//
// Created by mathis on 29/11/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API QuadLightSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the directionnal light.
     * @param parent - parent widget.
     */
    explicit QuadLightSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
