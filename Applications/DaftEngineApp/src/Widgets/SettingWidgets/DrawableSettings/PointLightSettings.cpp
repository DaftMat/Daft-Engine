//
// Created by daftmat on 28/09/2020.
//

#include "PointLightSettings.hpp"

namespace daft::app {
PointLightSettings::PointLightSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addIntSpinBoxVector("Color", 0, 255, 1, 255.f);
    addDoubleSpinBox("Intensity", 0, 9999);
}
};  // namespace daft::app
