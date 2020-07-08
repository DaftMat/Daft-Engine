//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Engine/Drawables/Drawable.hpp>

namespace daft::engine::objects {
class Light : public Drawable {
   public:
    using Mesh = core::geometry::Mesh;

    explicit Light(Mesh mesh = Mesh{}, const glm::vec3 &color = glm::vec3{1.f}) noexcept
        : m_mesh{std::move_if_noexcept(mesh)}, m_color{color} {}

    void prepare() override = 0;

    void render() override = 0;

    void unbind() override = 0;

    void translate(const glm::vec3 &t) override { Drawable::translate(t); }

    void rotate(const glm::vec3 &r) override { Drawable::rotate(r); }

    /**
     * no light can be scaled, nothing happens
     * @param s - new scale (won't be applied)
     */
    void rescale(const glm::vec3 &s) override {}

   private:
    Mesh m_mesh;
    glm::vec3 m_color;
};
}  // namespace daft::engine::objects