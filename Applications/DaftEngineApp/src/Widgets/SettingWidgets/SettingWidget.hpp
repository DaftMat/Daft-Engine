//
// Created by mathis on 12/07/2020.
//
#pragma once

#include <API.hpp>
#include <QtWidgets/QScrollArea>
#include <Widgets/SettingWidgets/DrawableSettings.hpp>
#include <memory>

#include "TransformSettings.hpp"

namespace daft::app {
class ENGINE_API SettingWidget : public QScrollArea {
   public:
    explicit SettingWidget(DrawableSettings *settings, TransformSettings *transforms, std::string name = "Drawable",
                           QWidget *parent = nullptr);

   signals:
    static void settingChanged() {}

   private:
    std::unique_ptr<DrawableSettings> m_settings{nullptr};
    std::unique_ptr<TransformSettings> m_transforms{nullptr};
};
}  // namespace daft::app