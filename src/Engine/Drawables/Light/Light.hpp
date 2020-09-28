//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Engine/Drawables/Drawable.hpp>

namespace daft::engine {
/**
 * Base class for any light in a 3D world.
 */
class Light : public Drawable {
   public:
    using Mesh = core::Mesh;

    /**
     * Default/standard constructor.
     * @param mesh - line mesh that represents the light.
     * @param color - color emitted by the light.
     */
    explicit Light(glm::vec3 color = glm::vec3{1.f}, Composite *parent = nullptr,
                   std::string name = "Light" + std::to_string(m_nrLight++))
        : Drawable(parent, std::move(name)), m_color{color} {}

    /**
     * Destructor.
     */
    ~Light() override { Light::reset(); }

    /**
     * Default move constructor.
     */
    Light(Light &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Light &operator=(Light &&) noexcept = default;

    /**
     * Renders the mesh representation of the light.
     */
    void render(const core::ShaderProgram &shader) override {}

    /**
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Translates the light.
     * @param t - translation to apply
     */
    void translate(glm::vec3 t) override { Drawable::translate(t); }

    /**
     * Rotates the light.
     * @param r - rotations to apply.
     */
    void rotate(glm::vec3 r) override { Drawable::rotate(r); }

    /**
     * Transformations setter using a SettingManager .
     * @param t - transformations.
     */
    void setTransformations(const core::SettingManager &t) override {}

    /**
     * Scales the light.
     * No light can be scaled, nothing happens.
     * @param s - new scale (won't be applied).
     */
    void rescale(glm::vec3 s) override {}

    /**
     * Accepts a DrawableVisitor .
     */
    void accept(DrawableVisitor *) override = 0;

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

    /**
     * Loads this light to a target shader as a uniform struct.
     * @param shader - shader to load the light to.
     * @param index - index of the light in its list.
     */
    virtual void loadToShader(const core::ShaderProgram &shader, int index) const = 0;

    /**
     * Resets the light.
     */
    void reset() override;

    /**
     * Gets the type of drawable.
     * @return nothing.
     */
    Type getType() override = 0;

    /**
     * Texts if this is a Composite .
     * @return false
     */
    [[nodiscard]] bool isComposite() const override { return false; }

    /**
     * Tests if this is an Object .
     * @return false.
     */
    [[nodiscard]] bool isObject() const override { return false; }

    /**
     * Tests if this is a Light .
     * @return true.
     */
    [[nodiscard]] bool isLight() const override { return true; }

   protected:
    Mesh m_mesh;

   private:
    glm::vec3 m_color;
    static int m_nrLight;
};
}  // namespace daft::engine