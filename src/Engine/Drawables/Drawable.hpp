//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <Core/Utils/Types.hpp>
#include <memory>

namespace daft {
/// forward declarations
namespace core::utils {
class DrawableVisitor;
}  // namespace core::utils

namespace core::geometry {
class ShaderProgram;
}

namespace engine::objects {
class Composite;

/**
 * Base class for any drawable object that will be rendered on the scene.
 */
class Drawable : public core::utils::NonCopyable {
   public:
    using DrawableVisitor = core::utils::DrawableVisitor;
    using Shader = core::geometry::ShaderProgram;

    /**
     * Standard constructor.
     * @param parent
     */
    explicit Drawable(Composite *parent = nullptr,
                      std::string name = "Drawable" + std::to_string(m_nrDrawables++)) noexcept;

    /**
     * renders the inner geometry.
     */
    virtual void render(const Shader &) = 0;

    /**
     * Accepts a DrawableVisitor .
     */
    virtual void accept(const DrawableVisitor *) = 0;

    /**
     * Calculates the transformation model matrix of the drawable.
     * @return transformation matrix.
     */
    [[nodiscard]] glm::mat4 model() const;

    /**
     * Calculates the normalized transformation model matrix of the drawable.
     * Will be used by the Gizmo s.
     * @return the transformation model matrix with a scale of 1.
     */
    [[nodiscard]] glm::mat4 normalizedModel() const;

    /**
     * Is the object selected by the user ?
     * @return true if the drawable is selected.
     */
    [[nodiscard]] inline bool selected() const { return m_selected; }

    /**
     * Selects the drawable.
     * selected() becomes true.
     */
    inline void select() { m_selected = true; }

    /**
     * Deselects the drawable.
     * selected() becomes false.
     */
    inline void deselect() { m_selected = false; }

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

    /**
     * Name constant reference.
     * @return const ref to name.
     */
    [[nodiscard]] inline const std::string &name() const { return m_name; }

    /**
     * Name reference.
     * @return ref to name.
     */
    inline std::string &name() { return m_name; }

    /**
     * Parent getter.
     * @return parent Composite .
     */
    [[nodiscard]] inline const Composite *getParent() const;

    /**
     * Parent setter.
     * @param composite - new parent.
     */
    inline void setParent(Composite *composite);

   private:
    [[nodiscard]] inline glm::mat4 calculateModel() const;

    [[nodiscard]] inline glm::mat4 calculateNormalizedModel() const;

    [[nodiscard]] inline glm::mat4 calculateScaleMat() const;

    [[nodiscard]] inline glm::mat4 calculateRotationMat() const;

    [[nodiscard]] inline glm::mat4 calculateTranslationMat() const;

    glm::vec3 m_position{0.f};
    glm::vec3 m_rotations{0.f};
    glm::vec3 m_scale{1.f};

    bool m_selected{false};

    std::shared_ptr<Composite> m_parent;
    std::string m_name;

    static int m_nrDrawables;
};
}  // namespace engine::objects
}  // namespace daft