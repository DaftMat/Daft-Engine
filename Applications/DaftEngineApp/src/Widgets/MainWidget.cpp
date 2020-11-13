//
// Created by mathis on 06/07/2020.
//
#include "MainWidget.hpp"

#include <Core/Utils/IO.hpp>
#include <Engine/Drawables/Object/Metaballs.hpp>
#include <QApplication>
#include <QDesktopWidget>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QPushButton>
#include <QSpacerItem>
#include <QWindow>
#include <QtWidgets/QLabel>
#include <Widgets/SettingWidgets/SettingWidget.hpp>
#include <Widgets/SettingWidgets/SettingWidgetVisitor.hpp>
#include <Widgets/TreeWidget/TreeWidget.hpp>
#include <src/Widgets/SettingWidgets/DrawableSettings/BallSettings.hpp>
#include <src/Widgets/SettingWidgets/DrawableSettings/PointSettings.hpp>

#include "BorderWidget.hpp"

namespace daft::app {
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), m_glWidget{std::make_unique<OpenGLWidget>()}, m_layout{std::make_unique<BorderLayout>(0)} {
    m_layout->setMargin(0);
    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);

    createNorthComponents();
    createSouthComponents();
    createEastComponents();

    setLayout(m_layout.get());

    /// signal connections
    connect(m_glWidget.get(), SIGNAL(selectionChanged()), this, SLOT(on_selectionChanged()));
    connect(m_glWidget.get(), SIGNAL(sceneTreeChanged()), this, SLOT(on_sceneTreeChanged()));
    connect(m_glWidget.get(), SIGNAL(glInitialized()), this, SLOT(on_glInitialized()));
}

MainWidget::~MainWidget() {
    m_glWidget.reset();
    m_layout.reset();
}

QFrame *MainWidget::createLine(QFrame::Shape shape) {
    auto frame = new QFrame();
    frame->setFrameShape(shape);
    frame->setFrameShadow(QFrame::Plain);
    return frame;
}

QSpacerItem *MainWidget::createHSpacer(int vsize) {
    return new QSpacerItem(vsize * 2, vsize, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem *MainWidget::createVSpacer(int hsize) {
    return new QSpacerItem(hsize, hsize * 2, QSizePolicy::Minimum, QSizePolicy::Expanding);
}

QDoubleSpinBox *MainWidget::createDoubleSpinBox(double val, double min, double max, double step, int decs) {
    auto spinbox = new QDoubleSpinBox();
    spinbox->setMinimum(min);
    spinbox->setMaximum(max);
    spinbox->setSingleStep(step);
    spinbox->setDecimals(decs);
    spinbox->setValue(val);
    return spinbox;
}

void MainWidget::on_selectionChanged() {
    auto selection = m_glWidget->renderer().getSelection();
    SettingWidget *widget;
    if (selection == nullptr) {
        widget = new SettingWidget(nullptr, nullptr, "", m_glWidget->renderer().exposure());
    } else if (!m_selectionIsDrawable && selection->getType() == engine::Drawable::Type::BSpline) {
        core::SettingManager sm;
        auto spline = (engine::BSpline *)selection;
        sm = selection->getSettings();
        widget =
            new SettingWidget(new PointSettings{sm}, nullptr, ("Point" + std::to_string(spline->getSelectedIndex())));
    } else if (!m_selectionIsDrawable && selection->getType() == engine::Drawable::Type::Metaballs) {
        core::SettingManager sm;
        auto metaball = (engine::Metaballs *)selection;
        sm = selection->getSettings();
        widget =
            new SettingWidget(new BallSettings{sm}, nullptr, ("Ball" + std::to_string(metaball->getSelectedIndex())));
    } else {
        auto visitor = std::make_unique<SettingWidgetVisitor>();
        selection->accept(visitor.get());
        widget = visitor->widget();
    }
    m_settingWidget.reset(widget);
    if (m_settingWidget->settingsWidget()) {
        connect(m_settingWidget->settingsWidget(), SIGNAL(settingChanged()), this, SLOT(on_settingChanged()));
        connect(m_settingWidget->settingsWidget(), SIGNAL(comboBoxChanged()), this,
                SLOT(on_selectionSettingsChanged()));
        if (m_selectionIsDrawable && selection && selection->getType() == engine::Drawable::Type::BSpline)
            connect(m_settingWidget->settingsWidget(), SIGNAL(bSplineAddPointButtonPressed()), this,
                    SLOT(on_bSplineAddButtonPressed()));
        else if (m_selectionIsDrawable && selection && selection->getType() == engine::Drawable::Type::Metaballs)
            connect(m_settingWidget->settingsWidget(), SIGNAL(metaballsAddPointButtonPressed()), this,
                    SLOT(on_metaballsAddButtonPressed()));
    }
    if (m_settingWidget->transformsWidget()) {
        connect(m_settingWidget->transformsWidget(), SIGNAL(settingChanged()), this, SLOT(on_settingChanged()));
    }
    m_selectionIsDrawable = true;
    m_southWidget->addWidget(m_settingWidget.get());
}

void MainWidget::on_settingChanged() {
    auto selection = m_glWidget->renderer().getSelection();
    if (selection) {
        std::stringstream ss;
        ss << "Setting of drawable changed. Drawable name : " << selection->name();
        core::Logger::info(std::move(ss));

        if (m_settingWidget->transformsWidget()) selection->setTransformations(m_settingWidget->transforms());
        if (m_settingWidget->settingsWidget()) selection->setSettings(m_settingWidget->settings());
    } else {
        float exposure = m_settingWidget->settingsWidget()->settings().get<float>("Exposure");
        m_glWidget->renderer().setExposure(exposure);
    }
    m_glWidget->update();
}

void MainWidget::on_sceneTreeChanged() {
    m_treeWidget->resetTree(m_glWidget->renderer().getSceneTree());
    connectSceneTreeEvents();
}

void MainWidget::on_treeSelectionChanged() {
    const auto index = m_treeWidget->selectionModel()->currentIndex();
    auto selectedText = index.data(Qt::DisplayRole).toString();

    const auto parent = index.parent();
    m_glWidget->setSelection(parent.data(Qt::DisplayRole).toString().toStdString());
    auto parentDrawable = m_glWidget->renderer().getSelection();

    if (parentDrawable && parentDrawable->getType() == engine::Drawable::Type::BSpline) {
        ((engine::BSpline *)parentDrawable)->setSelectedPoint(index.row());
        m_selectionIsDrawable = false;
    } else if (parentDrawable && parentDrawable->getType() == engine::Drawable::Type::Metaballs) {
        ((engine::Metaballs *)parentDrawable)->setSelectedBall(index.row());
        m_selectionIsDrawable = false;
    } else {
        m_glWidget->setSelection(selectedText.toStdString());
        auto selection = m_glWidget->renderer().getSelection();
        if (selection->getType() == engine::Drawable::Type::BSpline)
            ((engine::BSpline *)selection)->setSelectedPoint(-1);
        if (selection->getType() == engine::Drawable::Type::Metaballs)
            ((engine::Metaballs *)selection)->setSelectedBall(-1);
    }
    m_glWidget->update();
}

void MainWidget::on_treeItemChanged() {
    const auto index = m_treeWidget->selectionModel()->currentIndex();
    std::string newName = index.data(Qt::DisplayRole).toString().toStdString();
    m_glWidget->renderer().getSelection()->name() = newName;
    m_glWidget->setSelection(newName);
    m_settingWidget->setTitle(newName);
}

void MainWidget::on_glInitialized() {
    /// creates the tree widget.
    /// not possible in constructor :
    /// the function glInitialize() has not been called yet thus the renderer is nullptr.
    m_treeWidget = std::make_unique<TreeWidget>(m_glWidget->renderer().getSceneTree());
    connectSceneTreeEvents();
}

void MainWidget::connectSceneTreeEvents() {
    connect(m_treeWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            &MainWidget::on_treeSelectionChanged);
    connect(m_treeWidget->model(), &QStandardItemModel::dataChanged, this, &MainWidget::on_treeItemChanged);
    m_eastWidget->addWidget(m_treeWidget.get());
}

void MainWidget::createCreationComboBoxes() {
    std::vector<std::string> objects{"Sphere",      "Torus",     "Cube",  "Cylinder", "B-Spline",
                                     "2D B-Spline", "Metaballs", "Caves", "Group",    "Custom"};
    m_objectCreator = std::make_unique<QComboBox>();
    m_objectCreator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_objectCreator->addItem("Add object");
    for (const auto &obj : objects) {
        m_objectCreator->addItem(obj.c_str());
    }
    connect(m_objectCreator.get(), SIGNAL(currentIndexChanged(int)), this, SLOT(on_objectBoxChanged()));

    std::vector<std::string> lights{"Point Light", "Spot Light", "Directional Light"};
    m_lightCreator = std::make_unique<QComboBox>();
    m_lightCreator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lightCreator->addItem("Add light");
    for (const auto &light : lights) {
        m_lightCreator->addItem(light.c_str());
    }
    connect(m_lightCreator.get(), SIGNAL(currentIndexChanged(int)), this, SLOT(on_lightBoxChanged()));
}

void MainWidget::on_objectBoxChanged() {
    if (m_objectCreator->currentText() == "Add object")
        return;
    else if (m_objectCreator->currentText() == "Sphere")
        m_glWidget->addDrawable(engine::Drawable::Type::Sphere);
    else if (m_objectCreator->currentText() == "Torus")
        m_glWidget->addDrawable(engine::Drawable::Type::Torus);
    else if (m_objectCreator->currentText() == "Cube")
        m_glWidget->addDrawable(engine::Drawable::Type::Cube);
    else if (m_objectCreator->currentText() == "Cylinder")
        m_glWidget->addDrawable(engine::Drawable::Type::Cylinder);
    else if (m_objectCreator->currentText() == "B-Spline")
        m_glWidget->addDrawable(engine::Drawable::Type::BSpline);
    else if (m_objectCreator->currentText() == "2D B-Spline")
        m_glWidget->addDrawable(engine::Drawable::Type::BSpline2D);
    else if (m_objectCreator->currentText() == "Metaballs")
        m_glWidget->addDrawable(engine::Drawable::Type::Metaballs);
    else if (m_objectCreator->currentText() == "Caves")
        m_glWidget->addDrawable(engine::Drawable::Type::Caves);
    else if (m_objectCreator->currentText() == "Group")
        m_glWidget->addDrawable(engine::Drawable::Type::Group);
    else if (m_objectCreator->currentText() == "Custom") {
        auto fileName = QFileDialog::getOpenFileName(this, "Open Object", "/home", "Object Files (*.obj)");
        m_glWidget->addCustomObject(fileName.toStdString());
    }
    m_objectCreator->setCurrentIndex(0);
    m_glWidget->update();
}

void MainWidget::on_lightBoxChanged() {
    if (m_lightCreator->currentText() == "Add light")
        return;
    else if (m_lightCreator->currentText() == "Point Light")
        m_glWidget->addDrawable(engine::Drawable::Type::PointLight);
    else if (m_lightCreator->currentText() == "Spot Light")
        m_glWidget->addDrawable(engine::Drawable::Type::SpotLight);
    else if (m_lightCreator->currentText() == "Directional Light")
        m_glWidget->addDrawable(engine::Drawable::Type::DirLight);
    m_lightCreator->setCurrentIndex(0);
    m_glWidget->update();
}

void MainWidget::createShaderComboBox() {
    std::vector<std::string> shaders{"Blinn Phong", "Phong"};
    m_shaderBox = std::make_unique<QComboBox>();
    m_shaderBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    for (const auto &shader : shaders) {
        m_shaderBox->addItem(shader.c_str());
    }
    connect(m_shaderBox.get(), SIGNAL(currentIndexChanged(int)), this, SLOT(on_shaderBoxChanged()));
}

void MainWidget::on_shaderBoxChanged() {
    if (m_shaderBox->currentText() == "Blinn Phong")
        m_glWidget->renderer().setShader(engine::Renderer::AvailableShaders::BlinnPhong);
    else if (m_shaderBox->currentText() == "Phong")
        m_glWidget->renderer().setShader(engine::Renderer::AvailableShaders::Phong);
    m_glWidget->update();
}

void MainWidget::createRenderModeComboBox() {
    m_renderMode = std::make_unique<QComboBox>();
    m_renderMode->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_renderMode->addItem("Edition");
    m_renderMode->addItem("Rendering");
    connect(m_renderMode.get(), SIGNAL(currentIndexChanged(int)), this, SLOT(on_renderModeChanged()));
}

void MainWidget::on_renderModeChanged() {
    if (m_renderMode->currentIndex() == 0) {
        m_glWidget->renderer().switchToEditionMode();
    } else {
        m_glWidget->renderer().switchToRenderingMode();
    }
    m_glWidget->update();
}

void MainWidget::createNorthComponents() {
    createCreationComboBoxes();
    createShaderComboBox();
    createRenderModeComboBox();

    auto removeButton = new QPushButton();
    removeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    removeButton->setText("Remove");
    connect(removeButton, &QPushButton::pressed, this, &MainWidget::on_removeButtonPressed);

    m_northWidget = std::make_unique<BorderWidget>(BorderWidget::Orientation::HORIZONTAL, 70, 70);
    m_northWidget->addWidget(m_objectCreator.get());
    m_northWidget->addWidget(m_lightCreator.get());
    m_northWidget->addSeparator();
    m_northWidget->addWidget(removeButton);

    m_northWidget->addSpacer();

    auto formLayout = new QFormLayout{};
    formLayout->setMargin(1);
    formLayout->addRow("Shader", m_shaderBox.get());
    formLayout->addRow("Render Mode", m_renderMode.get());
    auto formWidget = new QWidget{};
    formWidget->setLayout(formLayout);
    m_northWidget->addWidget(formWidget);

    m_northWidget->setObjectName("northWidget");
    m_layout->addWidget(m_northWidget.get(), BorderLayout::Position::North);
}

void MainWidget::createSouthComponents() {
    auto screenHeight = float(QApplication::desktop()->screenGeometry().height());
    m_southWidget = std::make_unique<BorderWidget>(BorderWidget::Orientation::HORIZONTAL, int(screenHeight / 4.5f),
                                                   int(screenHeight / 4.5f));
    m_southWidget->addSpacer();
    m_southWidget->addSeparator();
    m_southWidget->setObjectName("southWidget");
    m_layout->addWidget(m_southWidget.get(), BorderLayout::Position::South);
}

void MainWidget::createEastComponents() {
    m_eastWidget = std::make_unique<BorderWidget>(BorderWidget::Orientation::VERTICAL, 150, 350);
    m_eastWidget->setObjectName("eastWidget");
    m_layout->addWidget(m_eastWidget.get(), BorderLayout::Position::East);
}

void MainWidget::on_bSplineAddButtonPressed() {
    auto spline = m_glWidget->renderer().getSelection();
    ((engine::BSpline *)spline)->addPoint();
    on_sceneTreeChanged();
    m_glWidget->update();
}

void MainWidget::on_metaballsAddButtonPressed() {
    auto mb = m_glWidget->renderer().getSelection();
    ((engine::Metaballs *)mb)->addBall();
    on_sceneTreeChanged();
    m_glWidget->update();
}

}  // namespace daft::app