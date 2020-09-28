//
// Created by mathis on 23/07/2020.
//
#pragma once

#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include <memory>
#include <unordered_map>
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
    explicit DrawableSettings(daft::core::SettingManager settings, QWidget* parent = nullptr);

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
     * @param divider - if the ints has to be divided into some floats. e.g. colors.
     */
    void addIntSpinBoxVector(std::string label, int min = 0, int max = 255, int step = 1, float multiplier = 1.f);

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
    void addComboBox(std::string label, const std::vector<std::string>& args, int currentItem = 0);

    /**
     * Settings constant reference getter.
     * @return const ref to the settings of the drawable.
     */
    [[nodiscard]] const core::SettingManager& settings() { return m_settings; }

    void mousePressEvent(QMouseEvent* event) override;

   public slots:
    void on_drawableChanged();
    void on_comboBoxChanged();
    void on_titleClicked();

   signals:
    void settingChanged();
    void comboBoxChanged();
    void titleClicked();
    void updateEvent();

   protected:
    void addField(std::string label, const std::vector<QWidget*>& widgets);

    daft::core::SettingManager m_settings;

   private:
    template <typename T>
    inline void setVector(const T& elem) {
        for (int i = 0; i < 3; ++i) m_settings.get<glm::vec3>(elem.first)[i] = elem.second[i]->value();
    }

    std::unordered_map<std::string, QSpinBox*> m_intSpinBoxes;
    std::unordered_map<std::string, QDoubleSpinBox*> m_doubleSpinBoxes;
    std::unordered_map<std::string, std::array<QSpinBox*, 3>> m_intSpinBoxVectors;
    std::unordered_map<std::string, std::array<QDoubleSpinBox*, 3>> m_doubleSpinBoxVectors;
    std::unordered_map<std::string, QComboBox*> m_comboBoxes;

    std::unique_ptr<QLabel> m_title{nullptr};
    std::unique_ptr<QFormLayout> m_layout{nullptr};
    std::unique_ptr<QWidget> m_widget{nullptr};
};
}  // namespace daft::app
