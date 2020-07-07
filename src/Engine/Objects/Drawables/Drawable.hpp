//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>

namespace daft::engine::objects {
/**
 * Base class for any drawable object that will be rendered on the scene.
 */
class Drawable : public core::utils::NonCopyable {
   public:
    /**
     * Default constructor.
     */
    Drawable() noexcept = default;

    /**
     * Default move constructor.
     */
    Drawable(Drawable &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return reference to this.
     */
    Drawable &operator=(Drawable &&) noexcept = default;

    /**
     * prepares the inner geometry to be rendered.
     */
    virtual void prepare() = 0;

    /**
     * renders the inner geometry.
     */
    virtual void render() = 0;

    /**
     * unbinds the inner geometry from the rendering context.
     */
    virtual void unbind() = 0;

    /**
     * Accepts a DrawableVisitor .
     */
    virtual void accept(/*DrawableVisitor **/) = 0;

    /**
     * Calculates the transformation model matrix of the drawable.
     * @return transformation matrix.
     */
    [[nodiscard]] inline glm::mat4 model() const;

    /**
     * Applies a translation to the drawable.
     * @param t - translation to apply.
     */
    virtual inline void translate(const glm::vec3 &t) { m_position += t; }

    /**
     * Applies a rotation to the drawable.
     * @param r - rotation to apply.
     */
    virtual inline void rotate(const glm::vec3 &r) { m_rotations += r; }

    /**
     * Re-scales the drawable.
     * @param s - new scale of the drawble.
     */
    virtual inline void rescale(const glm::vec3 &s) { m_scale = s; }

    /**
     * Position constant reference.
     * @return const ref to position.
     */
    [[nodiscard]] inline const glm::vec3 &position() const { return m_position; }

    /**
     * Position reference.
     * @return ref to position.
     */
    inline glm::vec3 &position() { return m_position; }

    /**
     * Rotations constant reference.
     * @return const ref to rotations.
     */
    [[nodiscard]] inline const glm::vec3 &rotations() const { return m_rotations; }

    /**
     * Rotations reference.
     * @return ref to rotations.
     */
    inline glm::vec3 &rotations() { return m_rotations; }

    /**
     * Scale constant reference.
     * @return const ref to scale.
     */
    [[nodiscard]] inline const glm::vec3 &scale() const { return m_scale; }

    /**
     * Scale reference.
     * @return ref to scale.
     */
    inline glm::vec3 &scale() { return m_scale; }

   private:
    [[nodiscard]] inline glm::mat4 calculateScaleMat() const;
    [[nodiscard]] inline glm::mat4 calculateRotationMat() const;
    [[nodiscard]] inline glm::mat4 calculateTranslationMat() const;

    glm::vec3 m_position;
    glm::vec3 m_rotations;
    glm::vec3 m_scale;
};
}  // namespace daft::engine::objects