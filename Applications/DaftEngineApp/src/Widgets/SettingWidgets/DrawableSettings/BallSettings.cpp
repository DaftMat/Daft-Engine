//
// Created by mathis on 27/10/2020.
//
#include "BallSettings.hpp"

namespace daft::app {
BallSettings::BallSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Position", -9999, 9999, 0.1);
    addDoubleSpinBox("Radius", 0, 9999, 0.1);
}
}  // namespace daft::app