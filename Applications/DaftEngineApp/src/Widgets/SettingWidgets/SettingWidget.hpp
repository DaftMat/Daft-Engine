//
// Created by mathis on 12/07/2020.
//
#pragma once

#include <API.hpp>
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

   public slots:
    void on_settingChanged() {
        std::stringstream ss;
        ss << "Setting changed."; /**TODO: implement.*/
        core::Logger::debug(std::move(ss));
    }

   private:
    std::unique_ptr<DrawableSettings> m_settings{nullptr};
    std::unique_ptr<TransformSettings> m_transforms{nullptr};
};
}  // namespace daft::app