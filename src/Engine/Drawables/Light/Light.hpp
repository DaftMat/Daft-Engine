//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Engine/Drawables/Drawable.hpp>

namespace daft::engine::objects {
/**
 * Base class for any light in a 3D world.
 */
class Light : public Drawable {
   public:
    using Mesh = core::geometry::Mesh;

    /**
     * Default/standard constructor.
     * @param mesh - line mesh that represents the light.
     * @param color - color emitted by the light.
     */
    explicit Light(Mesh mesh = Mesh{}, const glm::vec3 &color = glm::vec3{1.f}) noexcept
        : m_mesh{std::move_if_noexcept(mesh)}, m_color{color} {}

    /**
     * Renders the mesh representation of the light.
     */
    void render() override;

    /**
     * Translates the light.
     * @param t - translation to apply
     */
    void translate(const glm::vec3 &t) override { Drawable::translate(t); }

    /**
     * Rotates the light.
     * @param r - rotations to apply.
     */
    void rotate(const glm::vec3 &r) override { Drawable::rotate(r); }

    /**
     * Scales the light.
     * No light can be scaled, nothing happens.
     * @param s - new scale (won't be applied).
     */
    void rescale(const glm::vec3 &s) override {}

    /**
     * Accepts a DrawableVisitor .
     */
    void accept(const DrawableVisitor *) override = 0;

    /**
     * Emitted color constant reference.
     * @return color const ref.
     */
    const glm::vec3 &color() const { return m_color; }

    /**
     * Emitted color reference.
     * @return color ref.
     */
    glm::vec3 &color() { return m_color; }

   private:
    Mesh m_mesh;
    glm::vec3 m_color;
};
}  // namespace daft::engine::objects