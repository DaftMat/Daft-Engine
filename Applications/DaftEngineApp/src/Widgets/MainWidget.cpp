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
#include <Widgets/SettingWidgets/DrawableSettings.hpp>
#include <Widgets/SettingWidgets/TransformSettings.hpp>
#include <src/Widgets/SettingWidgets/SettingWidget.hpp>
#include <src/Widgets/SettingWidgets/SettingWidgetVisitor.hpp>

#include "BorderWidget.hpp"

namespace daft::app {
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), m_glWidget{std::make_unique<OpenGLWidget>()}, m_layout{std::make_unique<BorderLayout>(0)} {
    m_layout->setMargin(0);
    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);
    auto button0 = new QPushButton();
    button0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button0->setText("Button0");
    auto button1 = new QPushButton();
    button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button1->setText("Button1");
    auto button2 = new QPushButton();
    button2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button2->setText("Button2");
    auto northWidget = new BorderWidget(BorderWidget::Orientation::HORIZONTAL, 70, 70);
    northWidget->addWidget(button0);
    northWidget->addWidget(button1);
    northWidget->addSeparator();
    northWidget->addWidget(button2);
    northWidget->addSpacer();
    northWidget->setObjectName("northWidget");
    m_layout->addWidget(northWidget, BorderLayout::Position::North);

    auto screenHeight = float(QApplication::desktop()->screenGeometry().height());
    m_southWidget = std::make_unique<BorderWidget>(BorderWidget::Orientation::HORIZONTAL, int(screenHeight / 4.5f),
                                                   int(screenHeight / 4.5f));
    m_southWidget->addSpacer();
    m_southWidget->addSeparator();
    // core::mat::SettingManager settingsTransform;
    // settingsTransform.add("Position", glm::vec3{0.f, 0.f, 0.f});
    // settingsTransform.add("Rotations", glm::vec3{0.f, 0.f, 0.f});
    // settingsTransform.add("Scale", glm::vec3{1.f, 1.f, 1.f});
    // core::mat::SettingManager settings;
    // settings.add("test", glm::vec3{1.f, 2.f, 3.f});
    // auto drawSettings = new DrawableSettings(settings);
    // drawSettings->addDoubleSpinBoxVector("test");
    // auto transformSettings = new TransformSettings(settingsTransform);
    // auto settingWidget = new SettingWidget(drawSettings, transformSettings);
    // southWidget->addWidget(settingWidget);
    m_southWidget->setObjectName("southWidget");
    m_layout->addWidget(m_southWidget.get(), BorderLayout::Position::South);

    auto eastWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 150, 350);
    eastWidget->addWidget(createLabel("East"));
    eastWidget->setObjectName("eastWidget");
    m_layout->addWidget(eastWidget, BorderLayout::Position::East);

    auto westWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 0, 150);
    westWidget->addWidget(createLabel("West"));
    westWidget->setObjectName("westWidget");
    m_layout->addWidget(westWidget, BorderLayout::Position::West);

    setLayout(m_layout.get());

    connect(m_glWidget.get(), SIGNAL(selectionChanged()), this, SLOT(on_selectionChanged()));
}

MainWidget::~MainWidget() {
    m_glWidget.reset();
    m_layout.reset();
}

QLabel *MainWidget::createLabel(const QString &text) {
    auto label = new QLabel(text);
    // label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
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
    spinbox->setValue(val);
    spinbox->setMinimum(min);
    spinbox->setMaximum(max);
    spinbox->setSingleStep(step);
    spinbox->setDecimals(decs);
    return spinbox;
}

void MainWidget::on_selectionChanged() {
    auto selection = m_glWidget->renderer().getSelection();
    if (m_settingWidget != nullptr) m_southWidget->layout()->removeWidget(m_settingWidget.get());
    SettingWidget *widget;
    if (selection == nullptr) {
        widget = new SettingWidget(nullptr, nullptr);
    } else {
        auto visitor = new SettingWidgetVisitor();
        selection->accept(visitor);
        widget = visitor->widget();
    }
    m_settingWidget.reset(widget);
    m_southWidget->addWidget(m_settingWidget.get());
}
}  // namespace daft::app