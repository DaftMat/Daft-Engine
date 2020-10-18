//
// Created by mathis on 18/10/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API BSpline2DSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the B-Spline.
     * @param parent - parent widget.
     */
    explicit BSpline2DSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app