//
// Created by mathis on 12/07/2020.
//
#pragma once

#include <API.hpp>
#include <QtWidgets/QWidget>
#include <memory>

#include "TransformSettings.hpp"

namespace daft::app {
class ENGINE_API SettingWidget : public QWidget {
   public:
   signals:
    static void settingChanged() {}

   private:
    std::unique_ptr<TransformSettings> m_transforms;
};
}  // namespace daft::app