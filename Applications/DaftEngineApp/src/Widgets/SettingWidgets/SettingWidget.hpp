//
// Created by mathis on 12/07/2020.
//
#pragma once

#include <API.hpp>
#include <Engine/Drawables/Drawable.hpp>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <memory>

#include "DrawableSettings.hpp"
#include "TransformSettings.hpp"

namespace daft::app {
/**
 * A class that is used to edit the selected object's settings.
 */
class ENGINE_API SettingWidget : public QScrollArea {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - widget that edits object's special settings
     * @param transforms widget that edits object's transformations.
     * @param name - name of the object that is being edited.
     * @param parent - parent of the widget.
     */
    explicit SettingWidget(DrawableSettings *settings, TransformSettings *transforms, std::string name = "Drawable",
                           QWidget *parent = nullptr);

    /**
     * Gets the SettingManager from the DrawableSettings .
     * @return the specific settings of the selected Drawable as a SettingManager .
     */
    [[nodiscard]] core::SettingManager settings() const {
        return m_settings ? m_settings->settings() : core::SettingManager{};
    }

    /**
     * Gets the SettingManager from the TransformSettings .
     * @return the transformation settings of the selected Drawable as a SettingManager .
     */
    [[nodiscard]] core::SettingManager transforms() const {
        return m_transforms ? m_transforms->transforms() : core::SettingManager{};
    }

    /**
     * Getter of the inner DrawableSettings .
     * @return specific settings widget of the selected Drawable .
     */
    DrawableSettings *settingsWidget() { return m_settings.get(); }

    /**
     * Getter of the inner TransformSettings .
     * @return transformation settings widget of the selected Drawable .
     */
    TransformSettings *transformsWidget() { return m_transforms.get(); }

    /**
     * Sets the title of the section.
     * Always the name of the selected Drawable .
     * @param name - title to use.
     */
    void setTitle(const std::string &name);

   public slots:
    void on_updateEvent();

   private:
    void createWidgets();

    std::unique_ptr<DrawableSettings> m_settings{nullptr};
    std::unique_ptr<TransformSettings> m_transforms{nullptr};

    std::unique_ptr<QVBoxLayout> m_layout{nullptr};

    QLabel *m_title;
};
}  // namespace daft::app