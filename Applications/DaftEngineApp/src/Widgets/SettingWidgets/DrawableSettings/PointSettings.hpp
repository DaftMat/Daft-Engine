//
// Created by mathis on 28/09/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for a BSpline 's control point.
 */
class ENGINE_API PointSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the point (position).
     * @param parent - parent widget.
     */
    explicit PointSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app