//
// Created by mathis on 06/07/2020.
//
#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    m_glWidget = std::make_unique<OpenGLWidget>(this);
    m_layout = std::make_unique<BorderLayout>(0);

    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);
    m_layout->addWidget(createLabel("North"), BorderLayout::Position::North);
    m_layout->addWidget(createLabel("South"), BorderLayout::Position::South);
    m_layout->addWidget(createLabel("East"), BorderLayout::Position::East);
    m_layout->addWidget(createLabel("West"), BorderLayout::Position::West);
    setLayout(m_layout.get());
}

MainWidget::~MainWidget() {
    m_glWidget.reset();
    m_layout.reset();
}

QLabel *MainWidget::createLabel(const QString &text) const {
    auto label = new QLabel(text);
    label->setFrameStyle(QFrame::Box | QFrame::Raised);
    return label;
}
