//
// Created by mathis on 28/09/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API PointSettings : public DrawableSettings {
    Q_OBJECT

   public:
    explicit PointSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app