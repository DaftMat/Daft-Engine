//
// Created by mathis on 23/07/2020.
//
#include "DrawableSettings.hpp"

#include <QtWidgets/QLabel>
#include <src/Widgets/MainWidget.hpp>

#include "SettingWidget.hpp"

namespace daft::app {

DrawableSettings::DrawableSettings(daft::core::mat::SettingManager settings, QWidget* parent)
    : QWidget(parent), m_settings{std::move(settings)}, m_layout{new QFormLayout()} {
    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(2);

    if (!settings.empty()) {
        mainLayout->addWidget(new QLabel("Settings"));
        mainLayout->addWidget(MainWidget::createLine(QFrame::Shape::HLine));
    }

    auto formWidget = new QWidget;
    m_layout->setMargin(2);
    formWidget->setLayout(m_layout.get());
    mainLayout->addWidget(formWidget);

    setLayout(mainLayout);
}

void DrawableSettings::addIntSpinBox(std::string label, int min, int max, int step) {
    auto spinBox = new QSpinBox;
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setValue(m_settings.get<int>(label));
    spinBox->setSingleStep(step);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(onDrawableChanged()));
    m_intSpinBoxes.insert(std::make_pair(label, spinBox));
    addField(std::move(label), {spinBox});
}

void DrawableSettings::addDoubleSpinBox(std::string label, double min, double max, double step) {
    auto doubleSpinBox = new QDoubleSpinBox;
    doubleSpinBox->setMinimum(min);
    doubleSpinBox->setMaximum(max);
    doubleSpinBox->setValue(m_settings.get<double>(label));
    doubleSpinBox->setSingleStep(step);
    connect(doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onDrawableChanged()));
    m_doubleSpinBoxes.insert(std::make_pair(label, doubleSpinBox));
    addField(std::move(label), {doubleSpinBox});
}

void DrawableSettings::addIntSpinBoxVector(std::string label, int min, int max, int step) {
    std::array<QSpinBox*, 3> spinBoxVector{new QSpinBox, new QSpinBox, new QSpinBox};

    for (int i = 0; i < 3; ++i) spinBoxVector[i]->setValue(m_settings.get<glm::vec3>(label)[i]);

    std::for_each(spinBoxVector.begin(), spinBoxVector.end(), [min, max, step, this](QSpinBox* e) {
        e->setMinimum(min);
        e->setMaximum(max);
        e->setSingleStep(step);
        connect(e, SIGNAL(valueChanged(int)), this, SLOT(onDrawableChanged()));
    });

    m_intSpinBoxVectors.insert(std::make_pair(label, spinBoxVector));
    addField(std::move(label), {spinBoxVector[0], spinBoxVector[1], spinBoxVector[2]});
}

void DrawableSettings::addDoubleSpinBoxVector(std::string label, double min, double max, double step) {
    std::array<QDoubleSpinBox*, 3> doubleSpinBoxVector{new QDoubleSpinBox, new QDoubleSpinBox, new QDoubleSpinBox};

    for (int i = 0; i < 3; ++i) doubleSpinBoxVector[i]->setValue(m_settings.get<glm::vec3>(label)[i]);

    std::for_each(doubleSpinBoxVector.begin(), doubleSpinBoxVector.end(), [min, max, step, this](QDoubleSpinBox* e) {
        e->setMinimum(min);
        e->setMaximum(max);
        e->setSingleStep(step);
        connect(e, SIGNAL(valueChanged(double)), this, SLOT(onDrawableChanged()));
    });

    m_doubleSpinBoxVectors.insert(std::make_pair(label, doubleSpinBoxVector));
    addField(std::move(label), {doubleSpinBoxVector[0], doubleSpinBoxVector[1], doubleSpinBoxVector[2]});
}

void DrawableSettings::addComboBox(std::string label, const std::vector<std::string>& args) {
    auto comboBox = new QComboBox;
    for (const auto& arg : args) {
        comboBox->addItem(arg.c_str());
    }
    connect(comboBox, SIGNAL(selectionChanged(int)), this, SLOT(onDrawableChanged()));
    m_comboBoxes.insert(std::make_pair(label, comboBox));
    addField(std::move(label), {comboBox});
}

void DrawableSettings::addField(std::string label, const std::vector<QWidget*>& widgets) {
    auto widget = new QWidget;
    auto layout = new QHBoxLayout;
    layout->setMargin(2);
    for (auto w : widgets) layout->addWidget(w);
    widget->setLayout(layout);
    std::string lab = std::move(label);
    m_layout->addRow(lab.c_str(), widget);
}

void DrawableSettings::onDrawableChanged() {
    for (const auto& elem : m_intSpinBoxes) {
        m_settings.get<int>(elem.first) = elem.second->value();
    }
    for (const auto& elem : m_doubleSpinBoxes) {
        m_settings.get<double>(elem.first) = elem.second->value();
    }
    for (const auto& elem : m_intSpinBoxVectors) {
        setVector(elem);
    }
    for (const auto& elem : m_doubleSpinBoxVectors) {
        setVector(elem);
    }
    for (const auto& elem : m_comboBoxes) {
        m_settings.get<int>(elem.first) = elem.second->currentIndex();
    }
    core::utils::Logger::debug() << "Drawable changed.\n";
    emit settingChanged();
}

}  // namespace daft::app
