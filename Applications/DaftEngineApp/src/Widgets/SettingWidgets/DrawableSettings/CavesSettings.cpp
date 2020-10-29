//
// Created by mathis on 29/10/2020.
//
#include "CavesSettings.hpp"

namespace daft::app {
CavesSettings::CavesSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Grid Size", 1.0, 9999, 0.1);
    addDoubleSpinBox("Cube Size", 0.01, 9999, 0.1);
    addDoubleSpinBox("Iso Level", -99, 99, 0.1);
    addIntSpinBox("Seed", -9999, 9999, 1);
    addDoubleSpinBox("Scale", 1, 9999, 1);
    addIntSpinBox("Octaves", 1, 99, 1);
    addDoubleSpinBox("Persistence", 0, 99, 0.1);
    addDoubleSpinBox("Lacunarity", 0.1, 99, 0.1);
    addDoubleSpinBoxVector("Offset", -9999, 9999, 1);
}
}  // namespace daft::app