//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API CubeSettings : public DrawableSettings {
    Q_OBJECT

   public:
    explicit CubeSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
