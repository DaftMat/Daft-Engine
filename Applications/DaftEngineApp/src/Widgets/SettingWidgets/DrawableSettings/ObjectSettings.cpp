//
// Created by mathis on 23/07/2020.
//
#include "ObjectSettings.hpp"

#include <QtWidgets/QDoubleSpinBox>

namespace daft::app {
ObjectSettings::ObjectSettings(daft::core::mat::SettingManager *settings, QWidget *parent)
    : DrawableSettings(settings, parent) {
    std::vector<QWidget *> widgets;
    widgets.emplace_back(new QDoubleSpinBox);
    widgets.emplace_back(new QDoubleSpinBox);
    widgets.emplace_back(new QDoubleSpinBox);
    addField("Test", widgets);
}
}  // namespace daft::app