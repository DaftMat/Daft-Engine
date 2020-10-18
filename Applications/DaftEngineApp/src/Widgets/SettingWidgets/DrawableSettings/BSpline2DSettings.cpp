//
// Created by mathis on 18/10/2020.
//
#include "BSpline2DSettings.hpp"

namespace daft::app {
BSpline2DSettings::BSpline2DSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    /// doesn't work....
    addIntSpinBox("Base", 1, 99, 1);
    addDoubleSpinBox("Steps", 1, 9999, 1);
}
}  // namespace daft::app