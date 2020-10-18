//
// Created by mathis on 30/09/2020.
//
#include "SpotLightSettings.hpp"

namespace daft::app {
SpotLightSettings::SpotLightSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Color", 0.f, 255.f, 1.f);
    addDoubleSpinBox("Intensity", 0.f, 9999.f, 0.1f);
    addDoubleSpinBox("Inner angle", 0.f, 9999.f, 1.f);
    addDoubleSpinBox("Outer angle", 0.f, 9999.f, 1.f);
}
}  // namespace daft::app