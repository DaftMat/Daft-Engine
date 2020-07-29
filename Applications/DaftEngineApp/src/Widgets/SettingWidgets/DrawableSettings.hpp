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
/**
 * A class that is used to edit the selected object's special settings.
 * e.g. for an UV Sphere : meridians and parallels.
 */
class ENGINE_API DrawableSettings : public QWidget {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - library of the object's settings.
     * @param parent - parent of the widget.
     */
    explicit DrawableSettings(daft::core::mat::SettingManager settings, QWidget* parent = nullptr);

    /**
     * Destructor.
     */
    ~DrawableSettings() override { m_layout.reset(); }

    /**
     * Adds a QSpinBox to the form.
     * @param label - label of the form.
     * @param min - minimum value of the spin box.
     * @param max - maximum value of the spin box.
     * @param step - single step of the spin box.
     */
    void addIntSpinBox(std::string label, int min = 0, int max = 255, int step = 1);

    /**
     * Adds a QDoubleSpinBox to the form.
     * @param label - label of the form.
     * @param min - minimum value of the spin box.
     * @param max - maximum value of the spin box.
     * @param step - single step of the spin box.
     */
    void addDoubleSpinBox(std::string label, double min = -99, double max = 99, double step = 0.1);

    /**
     * Adds a row of 3 QSpinBox to the form.
     * @param label - label of the form.
     * @param min - minimum value of the spin boxes.
     * @param max - maximum value of the spin boxes.
     * @param step - single step of the spin boxes.
     */
    void addIntSpinBoxVector(std::string label, int min = 0, int max = 255, int step = 1);

    /**
     * Adds a row of 3 QDoubleSpinBox to the form.
     * @param label - label of the form.
     * @param min - minimum value of the spin boxes.
     * @param max - maximum value of the spin boxes.
     * @param step - single step of the spin boxes.
     */
    void addDoubleSpinBoxVector(std::string label, double min = -99, double max = 99, double step = 0.1);

    /**
     * Adds a QComboBox to the form.
     * @param label - label of the form.
     * @param args - text of each category of the combo box.
     */
    void addComboBox(std::string label, const std::vector<std::string>& args);

   public slots:
    void onDrawableChanged();

   signals:
    void settingChanged();

   private:
    void addField(std::string label, const std::vector<QWidget*>& widgets);

    template <typename T>
    void setVector(const T& elem);

    std::unordered_map<std::string, QSpinBox*> m_intSpinBoxes;
    std::unordered_map<std::string, QDoubleSpinBox*> m_doubleSpinBoxes;
    std::unordered_map<std::string, std::array<QSpinBox*, 3>> m_intSpinBoxVectors;
    std::unordered_map<std::string, std::array<QDoubleSpinBox*, 3>> m_doubleSpinBoxVectors;
    std::unordered_map<std::string, QComboBox*> m_comboBoxes;

    daft::core::mat::SettingManager m_settings;

    std::unique_ptr<QFormLayout> m_layout;
};
}  // namespace daft::app

#include <Widgets/SettingWidgets/DrawableSettings.inl>