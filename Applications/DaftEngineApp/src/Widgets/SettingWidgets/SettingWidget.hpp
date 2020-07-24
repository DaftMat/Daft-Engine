//
// Created by mathis on 12/07/2020.
//
#pragma once

#include <API.hpp>
#include <QtWidgets/QWidget>
#include <memory>
#include <src/Widgets/SettingWidgets/DrawableSettings/DrawableSettings.hpp>

#include "TransformSettings.hpp"

namespace daft::app {
class ENGINE_API SettingWidget : public QWidget {
   public:
    explicit SettingWidget(DrawableSettings *settings, QWidget *parent = nullptr);

   signals:
    static void settingChanged() {}

   private:
    std::unique_ptr<TransformSettings> m_transforms{nullptr};
    std::unique_ptr<DrawableSettings> m_settings{nullptr};
};
}  // namespace daft::app