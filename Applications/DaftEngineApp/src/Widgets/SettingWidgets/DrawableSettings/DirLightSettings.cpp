//
// Created by mathis on 03/10/2020.
//
#include "DirLightSettings.hpp"

namespace daft::app {
DirLightSettings::DirLightSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addIntSpinBoxVector("Color", 0, 255, 1, 255.f);
}
}  // namespace daft::app