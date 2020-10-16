//
// Created by mathis on 03/10/2020.
//
#include "DirLightSettings.hpp"

namespace daft::app {
DirLightSettings::DirLightSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Color", 0.f, 255.f, 1.f);
}
}  // namespace daft::app