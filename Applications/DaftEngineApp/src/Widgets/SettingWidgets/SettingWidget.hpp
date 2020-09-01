//
// Created by mathis on 12/07/2020.
//
#pragma once

#include <API.hpp>
#include <Engine/Drawables/Drawable.hpp>
#include <QtWidgets/QScrollArea>
#include <memory>

#include "DrawableSettings.hpp"
#include "SettingEditorVisitor.hpp"
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

    [[nodiscard]] core::SettingManager settings() const {
        return m_settings ? m_settings->settings() : core::SettingManager{};
    }

    [[nodiscard]] core::SettingManager transforms() const {
        return m_transforms ? m_transforms->transforms() : core::SettingManager{};
    }

    DrawableSettings *settingsWidget() { return m_settings.get(); }

    TransformSettings *transformsWidget() { return m_transforms.get(); }

   private:
    std::unique_ptr<DrawableSettings> m_settings{nullptr};
    std::unique_ptr<TransformSettings> m_transforms{nullptr};
};
}  // namespace daft::app