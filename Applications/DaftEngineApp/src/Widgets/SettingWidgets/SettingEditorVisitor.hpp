//
// Created by mathis on 29/08/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/Utils/DrawableVisitor.hpp>
#include <utility>

namespace daft::app {
class SettingEditorVisitor : public core::DrawableVisitor {
   public:
    /**
     * standard constructor.
     */
    SettingEditorVisitor(core::SettingManager settings, core::SettingManager transforms)
        : m_settings{std::move(settings)}, m_transforms{std::move(transforms)} {}

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

   private:
    core::SettingManager m_settings, m_transforms;
};
}  // namespace daft::app