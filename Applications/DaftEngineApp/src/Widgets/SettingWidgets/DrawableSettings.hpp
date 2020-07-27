//
// Created by mathis on 23/07/2020.
//
#pragma once

#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include <memory>
#include <utility>

namespace daft::app {
class ENGINE_API DrawableSettings : public QWidget {
    Q_OBJECT

   public:
    explicit DrawableSettings(daft::core::mat::SettingManager settings, QWidget* parent = nullptr);

    ~DrawableSettings() override { m_layout.reset(); }

    void addIntSpinBox(std::string label, int min = 0, int max = 255, int step = 1);

    void addDoubleSpinBox(std::string label, double min = -99, double max = 99, double step = 0.1);

    void addIntSpinBoxVector(std::string label, int min = 0, int max = 255, int step = 1);

    void addDoubleSpinBoxVector(std::string label, double min = -99, double max = 99, double step = 0.1);

    void addComboBox(std::string label, const std::vector<std::string>& args);

   public slots:
    void onDrawableChanged();

   signals:
    void settingChanged();

   private:
    void addField(std::string label, const std::vector<QWidget*>& widgets);

    std::unordered_map<std::string, QSpinBox*> m_intSpinBoxes;
    std::unordered_map<std::string, QDoubleSpinBox*> m_doubleSpinBoxes;
    std::unordered_map<std::string, std::array<QSpinBox*, 3>> m_intSpinBoxVectors;
    std::unordered_map<std::string, std::array<QDoubleSpinBox*, 3>> m_doubleSpinBoxVectors;
    std::unordered_map<std::string, QComboBox*> m_comboBoxes;

    daft::core::mat::SettingManager m_settings;

    std::unique_ptr<QFormLayout> m_layout;
};
}  // namespace daft::app