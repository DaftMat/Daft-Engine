//
// Created by daftmat on 28/09/2020.
//

#include "CubeSettings.hpp"

namespace daft::app {
CubeSettings::CubeSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addIntSpinBox("Resolution", 2, 9999, 1);
    addDoubleSpinBox("Radius", 0, 9999, 0.1);
}
}  // namespace daft::app