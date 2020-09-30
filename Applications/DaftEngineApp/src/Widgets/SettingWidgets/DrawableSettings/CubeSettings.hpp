//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for Cube objects.
 */
class ENGINE_API CubeSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the cube.
     * @param parent - parent widget.
     */
    explicit CubeSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
