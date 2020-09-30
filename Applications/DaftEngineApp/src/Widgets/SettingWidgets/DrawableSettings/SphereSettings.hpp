//
// Created by daftmat on 28/09/2020.
//

#pragma once

#include <Engine/Drawables/Object/Sphere.hpp>

#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for Sphere objects.
 */
class ENGINE_API SphereSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the sphere.
     * @param parent - parent widget.
     */
    explicit SphereSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
