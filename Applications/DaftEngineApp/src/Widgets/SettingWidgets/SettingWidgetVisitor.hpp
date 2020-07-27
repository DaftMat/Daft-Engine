//
// Created by mathis on 26/07/2020.
//
#pragma once

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Drawable.hpp>

#include "SettingWidget.hpp"

namespace daft::app {
class SettingWidgetVisitor : public core::utils::DrawableVisitor {
   public:
    void visit(engine::objects::Object *object) override;

    void visit(engine::objects::Composite *composite) override;

    SettingWidget *widget() { return m_widget; }

   private:
    template <typename D>
    TransformSettings *getTransforms(D *drawable);

    SettingWidget *m_widget{nullptr};
};
}  // namespace daft::app
#include <Widgets/SettingWidgets/SettingWidgetVisitor.inl>