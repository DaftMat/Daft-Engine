//
// Created by daftmat on 28/09/2020.
//

#include "PointLightSettings.hpp"

namespace daft::app {
PointLightSettings::PointLightSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Color", 0.f, 999.f, 0.1f);
    addDoubleSpinBox("Intensity", 0, 9999);
}
};  // namespace daft::app
