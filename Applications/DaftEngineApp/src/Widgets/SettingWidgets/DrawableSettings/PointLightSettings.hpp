//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for PointLight lights.
 */
class ENGINE_API PointLightSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the point light.
     * @param parent - parent widget.
     */
    explicit PointLightSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
