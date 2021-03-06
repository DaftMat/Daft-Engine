//
// Created by mathis on 23/07/2020.
//
#include "DrawableSettings.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QLabel>
#include <Widgets/MainWidget.hpp>

namespace daft::app {

DrawableSettings::DrawableSettings(daft::core::SettingManager settings, QWidget* parent)
    : QWidget(parent), m_settings{std::move(settings)}, m_layout{new QFormLayout()} {
    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(2);

    if (!m_settings.empty()) {
        m_title = std::make_unique<QLabel>("Settings");
        mainLayout->addWidget(m_title.get());
        mainLayout->addWidget(MainWidget::createLine(QFrame::Shape::HLine));
        connect(this, SIGNAL(titleClicked()), this, SLOT(on_titleClicked()));
    }

    m_widget = std::make_unique<QWidget>();
    m_layout->setMargin(2);
    m_widget->setLayout(m_layout.get());
    mainLayout->addWidget(m_widget.get());

    setLayout(mainLayout);

    auto screenWidth = float(QApplication::desktop()->screenGeometry().width());
    setMinimumWidth(int(screenWidth / 6.f));
}

void DrawableSettings::addIntSpinBox(std::string label, int min, int max, int step) {
    auto spinBox = new QSpinBox;
    spinBox->setMinimum(min);
    spinBox->setMaximum(max);
    spinBox->setValue(m_settings.get<int>(label));
    spinBox->setSingleStep(step);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(on_drawableChanged()));
    m_intSpinBoxes.insert(std::make_pair(label, spinBox));
    addField(std::move(label), {spinBox});
}

void DrawableSettings::addDoubleSpinBox(std::string label, double min, double max, double step) {
    auto doubleSpinBox = new QDoubleSpinBox;
    doubleSpinBox->setMinimum(min);
    doubleSpinBox->setMaximum(max);
    doubleSpinBox->setValue(double(m_settings.get<float>(label)));
    doubleSpinBox->setSingleStep(step);
    connect(doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(on_drawableChanged()));
    m_doubleSpinBoxes.insert(std::make_pair(label, doubleSpinBox));
    addField(std::move(label), {doubleSpinBox});
}

void DrawableSettings::addIntSpinBoxVector(std::string label, int min, int max, int step, float multiplier) {
    std::array<QSpinBox*, 3> spinBoxVector{new QSpinBox, new QSpinBox, new QSpinBox};

    for (int i = 0; i < 3; ++i) {
        spinBoxVector[i]->setMinimum(min);
        spinBoxVector[i]->setMaximum(max);
        spinBoxVector[i]->setValue(int(m_settings.get<glm::vec3>(label)[i] * multiplier));
        spinBoxVector[i]->setSingleStep(step);
        connect(spinBoxVector[i], SIGNAL(valueChanged(int)), this, SLOT(on_drawableChanged()));
    }

    m_intSpinBoxVectors.insert(std::make_pair(label, spinBoxVector));
    addField(std::move(label), {spinBoxVector[0], spinBoxVector[1], spinBoxVector[2]});
}

void DrawableSettings::addDoubleSpinBoxVector(std::string label, double min, double max, double step) {
    std::array<QDoubleSpinBox*, 3> doubleSpinBoxVector{new QDoubleSpinBox, new QDoubleSpinBox, new QDoubleSpinBox};

    for (int i = 0; i < 3; ++i) {
        doubleSpinBoxVector[i]->setMinimum(min);
        doubleSpinBoxVector[i]->setMaximum(max);
        doubleSpinBoxVector[i]->setValue(m_settings.get<glm::vec3>(label)[i]);
        doubleSpinBoxVector[i]->setSingleStep(step);
        connect(doubleSpinBoxVector[i], SIGNAL(valueChanged(double)), this, SLOT(on_drawableChanged()));
    }

    m_doubleSpinBoxVectors.insert(std::make_pair(label, doubleSpinBoxVector));
    addField(std::move(label), {doubleSpinBoxVector[0], doubleSpinBoxVector[1], doubleSpinBoxVector[2]});
}

void DrawableSettings::addComboBox(std::string label, const std::vector<std::string>& args, int currentItem) {
    auto comboBox = new QComboBox;
    for (const auto& arg : args) {
        comboBox->addItem(arg.c_str());
    }
    comboBox->setCurrentIndex(currentItem);

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_drawableChanged()));
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBoxChanged()));
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

void DrawableSettings::mousePressEvent(QMouseEvent* event) {
    if (m_title == nullptr) return;
    auto xLeft = m_title->x();
    auto yUp = m_title->y();
    auto xRight = xLeft + m_title->width();
    auto yBottom = yUp + m_title->height();

    if (event->x() > xLeft && event->y() > yUp && event->x() < xRight && event->y() < yBottom) emit titleClicked();
}

void DrawableSettings::on_drawableChanged() {
    for (const auto& elem : m_intSpinBoxes) {
        m_settings.get<int>(elem.first) = elem.second->value();
    }
    for (const auto& elem : m_doubleSpinBoxes) {
        m_settings.get<float>(elem.first) = float(elem.second->value());
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
    std::stringstream ss;
    ss << "Drawable changed.";
    core::Logger::debug(std::move(ss));
    emit settingChanged();
}

void DrawableSettings::on_comboBoxChanged() { emit comboBoxChanged(); }

void DrawableSettings::on_titleClicked() {
    m_widget->setVisible(!m_widget->isVisible());
    emit updateEvent();
}

}  // namespace daft::app
