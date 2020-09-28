//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API PointLightSettings : public DrawableSettings {
    Q_OBJECT

   public:
    explicit PointLightSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
