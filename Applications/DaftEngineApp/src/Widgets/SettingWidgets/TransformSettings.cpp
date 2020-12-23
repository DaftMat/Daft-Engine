//
// Created by mathis on 12/07/2020.
//
#include "TransformSettings.hpp"

#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <Widgets/MainWidget.hpp>

namespace daft::app {
TransformSettings::TransformSettings(daft::core::SettingManager settings, bool enablePos, bool enableRot,
                                     bool enableSca, QWidget *parent)
    : QWidget(parent), m_settings{std::move(settings)} {
    auto mainLayout = new QVBoxLayout();
    mainLayout->setMargin(2);

    m_title = std::make_unique<QLabel>("Transformations");
    mainLayout->addWidget(m_title.get());
    mainLayout->addWidget(MainWidget::createLine(QFrame::Shape::HLine));

    m_widget = std::make_unique<QWidget>();
    auto centreLayout = new QHBoxLayout();
    centreLayout->setMargin(2);

    auto position = createTransformWidget(Type::POSITION);
    position->setEnabled(enablePos);
    auto rotation = createTransformWidget(Type::ROTATION);
    rotation->setEnabled(enableRot);
    auto scale = createTransformWidget(Type::SCALE);
    scale->setEnabled(enableSca);

    centreLayout->addWidget(position);
    centreLayout->addWidget(rotation);
    centreLayout->addWidget(scale);

    m_widget->setLayout(centreLayout);
    connect(this, SIGNAL(titleClicked()), this, SLOT(on_titleClicked()));

    mainLayout->addWidget(m_widget.get());
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
    core::Logger::debug(std::move(ss));
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
                m_position[i]->setSingleStep(0.1);
                connect(m_position[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged()));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_position[i]);
            }
            break;
        case Type::ROTATION:
            layout->addWidget(new QLabel("Rotations"));
            for (int i = 0; i < 3; ++i) {
                m_rotations[i] = MainWidget::createDoubleSpinBox(m_settings.get<glm::vec3>("Rotations")[i]);
                m_rotations[i]->setSingleStep(1.0);
                connect(m_rotations[i], SIGNAL(valueChanged(double)), this, SLOT(onTransformChanged()));
                coordsLayout->addRow(new QLabel(labels[i].c_str()), m_rotations[i]);
            }
            break;
        case Type::SCALE:
            layout->addWidget(new QLabel("Scale"));
            for (int i = 0; i < 3; ++i) {
                m_scale[i] = MainWidget::createDoubleSpinBox(m_settings.get<glm::vec3>("Scale")[i]);
                m_scale[i]->setSingleStep(0.1);
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

void TransformSettings::on_titleClicked() {
    m_widget->setVisible(!m_widget->isVisible());
    emit updateEvent();
}

void TransformSettings::mousePressEvent(QMouseEvent *event) {
    if (m_title == nullptr) return;
    auto xLeft = m_title->x();
    auto yUp = m_title->y();
    auto xRight = xLeft + m_title->width();
    auto yBottom = yUp + m_title->height();

    if (event->x() > xLeft && event->y() > yUp && event->x() < xRight && event->y() < yBottom) emit titleClicked();
}
}  // namespace daft::app