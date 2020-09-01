//
// Created by mathis on 26/07/2020.
//
#pragma once

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Drawable.hpp>

#include "SettingWidget.hpp"

namespace daft::app {
/**
 * A visitor that creates the right SettingWidget according to the selected object.
 */
class SettingWidgetVisitor : public core::DrawableVisitor {
   public:
    /**
     * visits an Object .
     * @param object - object to visit.
     */
    void visit(engine::Object *object) override;

    /**
     * Visits a Sphere .
     * @param sphere - sphere to visit.
     */
    void visit(engine::Sphere *sphere) override;

    /**
     * visits a Composite .
     * @param composite - composite to visit.
     */
    void visit(engine::Composite *composite) override;

    /**
     * Created widget getter.
     * @return pointer to the created widget.
     */
    SettingWidget *widget() { return m_widget; }

   private:
    static TransformSettings *createTransformWidget(core::SettingManager sm) {
        return new TransformSettings(std::move(sm));
    }

    SettingWidget *m_widget{nullptr};
};
}  // namespace daft::app