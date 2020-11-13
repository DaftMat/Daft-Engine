//
// Created by mathis on 27/10/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for a BSpline 's control point.
 */
class ENGINE_API BallSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the ball (position + radius).
     * @param parent - parent widget.
     */
    explicit BallSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app
