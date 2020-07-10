//
// Created by mathis on 06/07/2020.
//
#include "MainWidget.hpp"

#include <Core/Utils/IO.hpp>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QtWidgets/QLabel>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent), m_layout{std::make_unique<BorderLayout>(0)} {
    m_glWidget = std::make_unique<OpenGLWidget>(this);

    m_layout->addWidget(m_glWidget.get(), BorderLayout::Position::Center);
    auto button = new QPushButton(this);
    button->setMinimumHeight(64);
    button->setMaximumHeight(64);
    button->setMaximumWidth(128);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setText("Button");
    // button->setStyleSheet("background-image: url(\"img/icon.png\")");
    auto northLayout = new QHBoxLayout();
    northLayout->addWidget(button);
    northLayout->addSpacerItem(createHSpacer());
    auto northWidget = new QWidget(this);
    northWidget->setLayout(northLayout);
    m_layout->addWidget(northWidget, BorderLayout::Position::North);
    m_layout->addWidget(createLabel("South"), BorderLayout::Position::South);
    m_layout->addWidget(createLabel("East"), BorderLayout::Position::East);
    m_layout->addWidget(createLabel("West"), BorderLayout::Position::West);

    setStyleSheet(daft::core::utils::IO::getStringFromFile("stylesheets/main.qss").c_str());
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
