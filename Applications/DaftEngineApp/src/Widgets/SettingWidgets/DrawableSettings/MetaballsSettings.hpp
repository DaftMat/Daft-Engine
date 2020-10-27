//
// Created by mathis on 27/10/2020.
//
#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
/**
 * DrawableSettings implementation for BSpline objects.
 */
class ENGINE_API MetaballsSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the Metaballs.
     * @param parent - parent widget.
     */
    explicit MetaballsSettings(core::SettingManager settings, QWidget *parent = nullptr);

   public slots:
    void on_AddButtonPressed();

   signals:
    void metaballsAddPointButtonPressed();
};
}  // namespace daft::app
