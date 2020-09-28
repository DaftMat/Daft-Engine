//
// Created by mathis on 28/09/2020.
//
#include "PointSettings.hpp"

namespace daft::app {
PointSettings::PointSettings(core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Position", -9999, 9999, 0.1);
}
}  // namespace daft::app
