//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for Torus objects.
 */
class ENGINE_API TorusSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the torus.
     * @param parent - parent widget.
     */
    explicit TorusSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
