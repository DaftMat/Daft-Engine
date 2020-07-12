//
// Created by mathis on 12/07/2020.
//
#include "TransformSettings.hpp"

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <Widgets/MainWidget.hpp>
#include <Widgets/SettingWidgets/SettingWidget.hpp>

namespace daft::app {
TransformSettings::TransformSettings(daft::core::mat::SettingManager *settings, QWidget *parent)
    : QWidget(parent), m_settings{settings} {
    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("Transformations"));
    mainLayout->addWidget(MainWidget::createLine(QFrame::Shape::HLine));

    auto centreWidget = new QWidget();
    auto centreLayout = new QHBoxLayout();

    centreLayout->addWidget(createTransformWidget(Type::POSITION));
    centreLayout->addWidget(createTransformWidget(Type::ROTATION));
    centreLayout->addWidget(createTransformWidget(Type::SCALE));

    centreWidget->setLayout(centreLayout);

    mainLayout->addWidget(centreWidget);
    setLayout(mainLayout);
}

TransformSettings::~TransformSettings() {
    for (int i = 0; i < 3; ++i) {
        delete m_position[i];
        delete m_rotations[i];
        delete m_scale[i];
    }
}

void TransformSettings::onTransformChanged(double val) {
    for (int i = 0; i < 3; ++i) {
        m_settings->get<glm::vec3>("position")[i] = m_position[i]->value();
        m_settings->get<glm::vec3>("rotations")[i] = m_rotations[i]->value();
        m_settings->get<glm::vec3>("scale")[i] = m_scale[i]->value();
    }
    APP_DEBUG("Transformation changed.");
    emit SettingWidget::settingChanged();
}

QWidget *TransformSettings::createTransformWidget(Type type) {
    auto widget = new QWidget();
    auto layout = new QVBoxLayout();

    auto coordsWidget = new QWidget();
    auto coordsLayout = new QFormLayout();

    std::vector<std::string> labels{"x ", "y ", "z "};

    std::string title;
    switch (type) {
        case Type::POSITION:
            layout->addWidget(new QLabel("Position"));
            for (int i = 0; i < 3; ++i) {
                m_position[i] = MainWidget::createDoubleSpinBox(m_settings->get<glm::vec3>("position")[i]);
                connect(m_position[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged(double)));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_position[i]);
            }
            break;
        case Type::ROTATION:
            layout->addWidget(new QLabel("Rotations"));
            for (int i = 0; i < 3; ++i) {
                m_rotations[i] = MainWidget::createDoubleSpinBox(m_settings->get<glm::vec3>("rotations")[i]);
                connect(m_rotations[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged(double)));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_rotations[i]);
            }
            break;
        case Type::SCALE:
            layout->addWidget(new QLabel("Scale"));
            for (int i = 0; i < 3; ++i) {
                m_scale[i] = MainWidget::createDoubleSpinBox(m_settings->get<glm::vec3>("scale")[i]);
                connect(m_scale[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged(double)));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_scale[i]);
            }
            break;
    }

    coordsWidget->setLayout(coordsLayout);

    layout->addWidget(coordsWidget);
    widget->setLayout(layout);
    return widget;
}
}  // namespace daft::app