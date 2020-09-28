//
// Created by daftmat on 28/09/2020.
//

#include "TorusSettings.hpp"

namespace daft::app {
TorusSettings::TorusSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addIntSpinBox("Meridians", 3, 9999, 1);
    addIntSpinBox("Parallels", 3, 9999, 1);
    addDoubleSpinBox("Inner Radius", 0, 9999, 0.1);
    addDoubleSpinBox("Outer Radius", 0, 9999, 0.1);
}
}  // namespace daft::app
