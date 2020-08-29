//
// Created by mathis on 29/08/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::app {
class SettingEditorVisitor : public core::DrawableVisitor {
   public:
    /**
     * standard constructor.
     */
    SettingEditorVisitor(const core::SettingManager &settings, const core::SettingManager &transforms)
        : m_settings{settings}, m_transforms{transforms} {}

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
    template <typename D>
    void updateTransforms(D *drawable) {
        drawable->position() = m_transforms.get<glm::vec3>("Position");
        drawable->rotations() = m_transforms.get<glm::vec3>("Rotations");
        drawable->scale() = m_transforms.get<glm::vec3>("Scale");
    }

    core::SettingManager m_settings, m_transforms;
};
}  // namespace daft::app