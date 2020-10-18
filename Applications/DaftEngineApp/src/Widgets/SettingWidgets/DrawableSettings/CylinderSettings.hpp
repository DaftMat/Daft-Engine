//
// Created by mathis on 05/10/2020.
//
#pragma once
#include <API.hpp>

#include "DrawableSettings.hpp"

namespace daft::app {
class CylinderSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the cylinder.
     * @param parent - parent widget.
     */
    explicit CylinderSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app