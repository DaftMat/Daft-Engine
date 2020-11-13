//
// Created by mathis on 03/10/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API DirLightSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the directionnal light.
     * @param parent - parent widget.
     */
    explicit DirLightSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app