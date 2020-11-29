//
// Created by mathis on 29/11/2020.
//
#include "QuadLightSettings.hpp"

daft::app::QuadLightSettings::QuadLightSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBoxVector("Color", 0.f, 999.f, 0.1f);
    addDoubleSpinBox("Intensity", 0.f, 999.f, 0.1f);
    addDoubleSpinBox("Width", 0.f, 999.f, 0.1f);
    addDoubleSpinBox("Height", 0.f, 999.f, 0.1f);
}
