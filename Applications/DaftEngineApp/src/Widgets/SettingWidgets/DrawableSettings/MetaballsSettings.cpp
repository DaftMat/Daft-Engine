//
// Created by mathis on 27/10/2020.
//
#include "MetaballsSettings.hpp"

#include <QtWidgets/QPushButton>

namespace daft::app {
MetaballsSettings::MetaballsSettings(daft::core::SettingManager settings, QWidget *parent)
    : DrawableSettings(std::move(settings), parent) {
    addDoubleSpinBox("Cube Size", 1, 9999, 0.1);
    auto addButton = new QPushButton{"Add Ball"};
    addField("", {addButton});

    connect(addButton, SIGNAL(pressed()), this, SLOT(on_AddButtonPressed()));
}

void MetaballsSettings::on_AddButtonPressed() { emit metaballsAddPointButtonPressed(); }
}  // namespace daft::app