//
// Created by mathis on 05/10/2020.
//
#include "CylinderSettings.hpp"

namespace daft::app {
CylinderSettings::CylinderSettings(core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addIntSpinBox("Meridians", 3, 9999, 1);
    addIntSpinBox("Parallels", 3, 9999, 1);
    addDoubleSpinBox("Radius", 0, 9999, 0.1);
    addDoubleSpinBoxVector("Rotations Joint 1", -999, 999, 1.0);
    addDoubleSpinBoxVector("Rotations Joint 2", -999, 999, 1.0);
}
}  // namespace daft::app