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
TransformSettings::TransformSettings(daft::core::mat::SettingManager settings, QWidget *parent)
    : QWidget(parent), m_settings{std::move(settings)} {
    auto mainLayout = new QVBoxLayout();
    mainLayout->setMargin(2);

    mainLayout->addWidget(new QLabel("Transformations"));
    mainLayout->addWidget(MainWidget::createLine(QFrame::Shape::HLine));

    auto centreWidget = new QWidget();
    auto centreLayout = new QHBoxLayout();
    centreLayout->setMargin(2);

    centreLayout->addWidget(createTransformWidget(Type::POSITION));
    centreLayout->addWidget(createTransformWidget(Type::ROTATION));
    centreLayout->addWidget(createTransformWidget(Type::SCALE));

    centreWidget->setLayout(centreLayout);

    mainLayout->addWidget(centreWidget);
    setLayout(mainLayout);
}

void TransformSettings::onTransformChanged() {
    for (int i = 0; i < 3; ++i) {
        m_settings.get<glm::vec3>("Position")[i] = m_position[i]->value();
        m_settings.get<glm::vec3>("Rotations")[i] = m_rotations[i]->value();
        m_settings.get<glm::vec3>("Scale")[i] = m_scale[i]->value();
    }
    std::stringstream ss;
    ss << "Transformation changed.";
    core::utils::Logger::debug(std::move(ss));
    emit settingChanged();
}

QWidget *TransformSettings::createTransformWidget(Type type) {
    auto widget = new QWidget();
    auto layout = new QVBoxLayout();
    layout->setMargin(0);

    auto coordsWidget = new QWidget();
    auto coordsLayout = new QFormLayout();
    coordsLayout->setMargin(0);

    std::vector<std::string> labels{"x ", "y ", "z "};

    std::string title;
    switch (type) {
        case Type::POSITION:
            layout->addWidget(new QLabel("Position"));
            for (int i = 0; i < 3; ++i) {
                m_position[i] = MainWidget::createDoubleSpinBox(m_settings.get<glm::vec3>("Position")[i]);
                connect(m_position[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged()));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_position[i]);
            }
            break;
        case Type::ROTATION:
            layout->addWidget(new QLabel("Rotations"));
            for (int i = 0; i < 3; ++i) {
                m_rotations[i] = MainWidget::createDoubleSpinBox(m_settings.get<glm::vec3>("Rotations")[i]);
                connect(m_rotations[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged()));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_rotations[i]);
            }
            break;
        case Type::SCALE:
            layout->addWidget(new QLabel("Scale"));
            for (int i = 0; i < 3; ++i) {
                m_scale[i] = MainWidget::createDoubleSpinBox(m_settings.get<glm::vec3>("Scale")[i]);
                connect(m_scale[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged()));
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