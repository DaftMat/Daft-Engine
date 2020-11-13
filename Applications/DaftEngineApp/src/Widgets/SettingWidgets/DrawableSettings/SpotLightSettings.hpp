//
// Created by mathis on 30/09/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for PointLight lights.
 */
class ENGINE_API SpotLightSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the spot light.
     * @param parent - parent widget.
     */
    explicit SpotLightSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app