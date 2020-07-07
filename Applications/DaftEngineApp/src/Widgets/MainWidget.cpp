//
// Created by mathis on 06/07/2020.
//
#include "MainWidget.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QtWidgets/QLabel>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
    m_glWidget = std::make_unique<OpenGLWidget>(this);
    m_layout = std::make_unique<BorderLayout>(0);

    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);
    auto button = new QPushButton(this);
    button->setMinimumSize(64, 64);
    button->setMaximumSize(64, 64);
    button->setStyleSheet("background-image: url(\"img/icon.png\")");
    auto northLayout = new QHBoxLayout();
    northLayout->addWidget(button);
    northLayout->addSpacerItem(createHSpacer());
    auto northWidget = new QWidget(this);
    northWidget->setLayout(northLayout);
    m_layout->addWidget(northWidget, BorderLayout::Position::North);
    m_layout->addWidget(createLabel("South"), BorderLayout::Position::South);
    m_layout->addWidget(createLabel("East"), BorderLayout::Position::East);
    m_layout->addWidget(createLabel("West"), BorderLayout::Position::West);

    setStyleSheet("color: #f6f6f6; background-color: #404040");
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

QSpacerItem *MainWidget::createHSpacer(int vsize) const {
    return new QSpacerItem(vsize * 2, vsize, QSizePolicy::Expanding, QSizePolicy::Minimum);
}

QSpacerItem *MainWidget::createVSpacer(int hsize) const {
    return new QSpacerItem(hsize, hsize * 2, QSizePolicy::Minimum, QSizePolicy::Expanding);
}
