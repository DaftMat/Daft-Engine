//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API TorusSettings : public DrawableSettings {
    Q_OBJECT

   public:
    explicit TorusSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
