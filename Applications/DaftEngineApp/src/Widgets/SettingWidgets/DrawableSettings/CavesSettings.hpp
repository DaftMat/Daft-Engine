//
// Created by mathis on 29/10/2020.
//
#pragma once
#include <API.hpp>

#include "DrawableSettings.hpp"

namespace daft::app {
class ENGINE_API CavesSettings : public DrawableSettings {
    Q_OBJECT

   public:
    /**
     * Constructor.
     * @param settings - settings of the Caves .
     * @param parent - parent widget.
     */
    explicit CavesSettings(core::SettingManager settings, QWidget *parent = nullptr);
};
}  // namespace daft::app