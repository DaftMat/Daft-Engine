//
// Created by mathis on 23/07/2020.
//
#pragma once
#include <API.hpp>

#include "DrawableSettings.hpp"

namespace daft::app {
class ObjectSettings : public DrawableSettings {
   public:
    explicit ObjectSettings(daft::core::mat::SettingManager *settings, QWidget *parent = nullptr);

   public slots:
    void onDrawableChanged() override { APP_INFO("Drawable changed."); }
};
}  // namespace daft::app