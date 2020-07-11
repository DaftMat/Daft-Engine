//
// Created by mathis on 06/07/2020.
//
#include "MainWidget.hpp"

#include <Core/Utils/IO.hpp>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QtWidgets/QLabel>

#include "BorderWidget.hpp"

namespace daft::app {
MainWidget::MainWidget(QWidget *parent) : QWidget(parent), m_layout{std::make_unique<BorderLayout>(0)} {
    m_glWidget = std::make_unique<OpenGLWidget>(this);

    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);
    auto button = new QPushButton(this);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setText("Button");
    // button->setStyleSheet("background-image: url(\"img/icon.png\")");
    auto northWidget = new BorderWidget(BorderWidget::Orientation::HORIZONTAL, 70, this);
    northWidget->addWidget(button);
    northWidget->addSeparator();
    northWidget->addSpacer();
    m_layout->addWidget(northWidget, BorderLayout::Position::North);

    auto southWidget = new BorderWidget(BorderWidget::Orientation::HORIZONTAL, 170, this);
    southWidget->addWidget(createLabel("South"));
    m_layout->addWidget(southWidget, BorderLayout::Position::South);

    auto eastWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 150, this);
    eastWidget->addWidget(createLabel("East"));
    m_layout->addWidget(eastWidget, BorderLayout::Position::East);

    auto westWidget = new BorderWidget(BorderWidget::Orientation::VERTICAL, 0, this);
    westWidget->addWidget(createLabel("West"));
    m_layout->addWidget(westWidget, BorderLayout::Position::West);

    setLayout(m_layout.get());
}

MainWidget::~MainWidget() {
    m_glWidget.reset();
    m_layout.reset();
}

QLabel *MainWidget::createLabel(const QString &text) {
    auto label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}

QSpacerItem *MainWidget::createHSpacer(int vsize) {
    return new QSpacerItem(vsize * 2, vsize, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem *MainWidget::createVSpacer(int hsize) {
    return new QSpacerItem(hsize, hsize * 2, QSizePolicy::Minimum, QSizePolicy::Expanding);
}
}  // namespace daft::app