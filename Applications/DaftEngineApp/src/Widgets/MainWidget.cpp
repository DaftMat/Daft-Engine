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
#include <QtWidgets/QScrollArea>
#include <src/Widgets/SettingWidgets/DrawableSettings/ObjectSettings.hpp>
#include <src/Widgets/SettingWidgets/TransformSettings.hpp>

#include "BorderWidget.hpp"

namespace daft::app {
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), m_glWidget{std::make_unique<OpenGLWidget>()}, m_layout{std::make_unique<BorderLayout>(0)} {
    m_layout->setMargin(2);
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
    // button->setStyleSheet("background-image: url(\"img/icon.png\")");
    auto northWidget = new BorderWidget(BorderWidget::Orientation::HORIZONTAL, 70, 70);
    northWidget->addWidget(button0);
    northWidget->addWidget(button1);
    northWidget->addSeparator();
    northWidget->addWidget(button2);
    northWidget->addSpacer();
    northWidget->setObjectName("northWidget");
    m_layout->addWidget(northWidget, BorderLayout::Position::North);

    auto screenHeight = float(QApplication::desktop()->screenGeometry().height());
    auto southWidget = new BorderWidget(BorderWidget::Orientation::HORIZONTAL, 70, int(screenHeight / 6.f));
    southWidget->addSpacer();
    southWidget->addSeparator();
    auto settings = new core::mat::SettingManager();
    settings->add("position", glm::vec3{0.f, 0.f, 0.f});
    settings->add("rotations", glm::vec3{0.f, 0.f, 0.f});
    settings->add("scale", glm::vec3{1.f, 1.f, 1.f});
    auto settingScrollArea = new QScrollArea();
    auto settingWidget = new QWidget();
    auto settingLayout = new QVBoxLayout();
    settingLayout->addWidget(new ObjectSettings(new core::mat::SettingManager()));
    settingLayout->addWidget(new ObjectSettings(new core::mat::SettingManager()));
    settingLayout->addWidget(new ObjectSettings(new core::mat::SettingManager()));
    settingLayout->addWidget(new TransformSettings(settings));
    settingWidget->setLayout(settingLayout);
    settingScrollArea->setWidget(settingWidget);
    settingScrollArea->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    southWidget->addWidget(settingScrollArea);
    southWidget->setObjectName("southWidget");
    m_layout->addWidget(southWidget, BorderLayout::Position::South);

    auto eastWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 150, 350);
    eastWidget->addWidget(createLabel("East"));
    eastWidget->setObjectName("eastWidget");
    m_layout->addWidget(eastWidget, BorderLayout::Position::East);

    auto westWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 0, 150);
    westWidget->addWidget(createLabel("West"));
    westWidget->setObjectName("westWidget");
    m_layout->addWidget(westWidget, BorderLayout::Position::West);

    setLayout(m_layout.get());
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
}  // namespace daft::app