//
// Created by mathis on 06/07/2020.
//
#include "MainWidget.hpp"

#include <Core/Utils/IO.hpp>
#include <QApplication>
#include <QDesktopWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QtWidgets/QLabel>
#include <Widgets/SettingWidgets/SettingWidget.hpp>
#include <Widgets/SettingWidgets/SettingWidgetVisitor.hpp>
#include <Widgets/TreeWidget/TreeWidget.hpp>

#include "BorderWidget.hpp"

namespace daft::app {
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), m_glWidget{std::make_unique<OpenGLWidget>()}, m_layout{std::make_unique<BorderLayout>(0)} {
    m_layout->setMargin(0);
    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);

    /// NORTH
    auto addGroup = new QPushButton();
    addGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addGroup->setText("Add Group");
    auto addSphere = new QPushButton();
    addSphere->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    addSphere->setText("Add Sphere");
    auto removeButton = new QPushButton();
    removeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    removeButton->setText("Remove");

    connect(addGroup, &QPushButton::pressed, this, &MainWidget::on_addGroupButtonPressed);
    connect(addSphere, &QPushButton::pressed, this, &MainWidget::on_addSphereButtonPressed);
    connect(removeButton, &QPushButton::pressed, this, &MainWidget::on_removeButtonPressed);

    auto northWidget = new BorderWidget(BorderWidget::Orientation::HORIZONTAL, 70, 70);
    northWidget->addWidget(addGroup);
    northWidget->addWidget(addSphere);
    northWidget->addSeparator();
    northWidget->addWidget(removeButton);
    northWidget->addSpacer();
    northWidget->setObjectName("northWidget");
    m_layout->addWidget(northWidget, BorderLayout::Position::North);

    /// SOUTH
    auto screenHeight = float(QApplication::desktop()->screenGeometry().height());
    m_southWidget = std::make_unique<BorderWidget>(BorderWidget::Orientation::HORIZONTAL, int(screenHeight / 4.5f),
                                                   int(screenHeight / 4.5f));
    m_southWidget->addSpacer();
    m_southWidget->addSeparator();
    m_southWidget->setObjectName("southWidget");
    m_layout->addWidget(m_southWidget.get(), BorderLayout::Position::South);

    /// EAST
    m_eastWidget = std::make_unique<BorderWidget>(BorderWidget::Orientation::VERTICAL, 150, 350);
    m_eastWidget->setObjectName("eastWidget");
    m_layout->addWidget(m_eastWidget.get(), BorderLayout::Position::East);

    /// WEST
    /// auto westWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 0, 150);
    /// westWidget->setObjectName("westWidget");
    /// m_layout->addWidget(westWidget, BorderLayout::Position::West);

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
        widget = new SettingWidget(nullptr, nullptr);
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
    }
    if (m_settingWidget->transformsWidget()) {
        connect(m_settingWidget->transformsWidget(), SIGNAL(settingChanged()), this, SLOT(on_settingChanged()));
    }
    m_southWidget->addWidget(m_settingWidget.get());
}

void MainWidget::on_settingChanged() {
    auto selection = m_glWidget->renderer().getSelection();
    if (!selection) return;

    std::stringstream ss;
    ss << "Setting of drawable changed. Drawable name : " << selection->name();
    core::Logger::error(std::move(ss));

    selection->setTransformations(m_settingWidget->transforms());
    selection->setSettings(m_settingWidget->settings());
    m_glWidget->update();
}

void MainWidget::on_sceneTreeChanged() {
    m_treeWidget->resetTree(m_glWidget->renderer().getSceneTree());
    connectSceneTreeEvents();
}

void MainWidget::on_treeSelectionChanged() {
    const auto index = m_treeWidget->selectionModel()->currentIndex();
    auto selectedText = index.data(Qt::DisplayRole).toString();
    m_glWidget->setSelection(selectedText.toStdString());
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

}  // namespace daft::app