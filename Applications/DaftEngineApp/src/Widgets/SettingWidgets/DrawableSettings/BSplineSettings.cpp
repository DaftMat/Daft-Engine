//
// Created by daftmat on 28/09/2020.
//

#include "BSplineSettings.hpp"

#include <QtWidgets/QPushButton>

namespace daft::app {
BSplineSettings::BSplineSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addIntSpinBox("Base", 1, 99, 1);
    addDoubleSpinBox("Steps", 1, 9999, 1);
    auto addButton = new QPushButton{"Add Point"};
    addField("", {addButton});

    connect(addButton, SIGNAL(pressed()), this, SLOT(on_AddButtonPressed()));
}

void BSplineSettings::on_AddButtonPressed() { emit bSplineAddPointButtonPressed(); }
}  // namespace daft::app