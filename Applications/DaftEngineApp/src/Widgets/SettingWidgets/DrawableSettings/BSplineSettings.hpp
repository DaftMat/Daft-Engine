//
// Created by daftmat on 28/09/2020.
//

#pragma once
#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API BSplineSettings : public DrawableSettings {
    Q_OBJECT

   public:
    explicit BSplineSettings(core::SettingManager settings, QWidget *parent = nullptr);

   public slots:
    void on_AddButtonPressed();

   signals:
    void bSplineAddPointButtonPressed();
};
}  // namespace daft::app
