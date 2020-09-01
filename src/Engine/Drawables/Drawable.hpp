//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/ShaderProgram.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <Core/Utils/Types.hpp>

namespace daft {
/// forward declarations
namespace core {
class DrawableVisitor;
}  // namespace core

namespace engine {
class Composite;

/**
 * Base class for any drawable object that will be rendered on the scene.
 */
class Drawable : public core::NonCopyable {
   public:
    using DrawableVisitor = core::DrawableVisitor;

    /**
     * Standard constructor.
     * @param parent
     */
    explicit Drawable(Composite *parent = nullptr,
                      std::string name = "Drawable" + std::to_string(m_nrDrawables++)) noexcept;

    virtual ~Drawable() noexcept = default;

    Drawable(Drawable &&) noexcept = default;

    Drawable &operator=(Drawable &&) noexcept = default;

    /**
     * renders the inner geometry.
     */
    virtual void render(const core::ShaderProgram &shader) = 0;

    /**
     * Accepts a DrawableVisitor .
     */
    virtual void accept(DrawableVisitor *) = 0;

    /**
     * Object accessor.
     * @param name - name of the object we're looking for.
     * @return the object if it's the right name. nullptr otherwise.
     */
    virtual Drawable *find(const std::string &name);

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
    [[nodiscard]] bool selected() const { return m_selected; }

    /**
     * Selects the drawable.
     * selected() becomes true.
     */
    void select() { m_selected = true; }

    /**
     * Deselects the drawable.
     * selected() becomes false.
     */
    void unselect() { m_selected = false; }

    /**
     * Applies a translation to the drawable.
     * @param t - translation to apply.
     */
    virtual void translate(const glm::vec3 &t) { m_position += t; }

    /**
     * Applies a rotation to the drawable.
     * @param r - rotation to apply.
     */
    virtual void rotate(const glm::vec3 &r) { m_rotations += r; }

    /**
     * Re-scales the drawable.
     * @param s - new scale of the drawble.
     */
    virtual void rescale(const glm::vec3 &s) { m_scale = s; }

    /**
     * Position constant reference.
     * @return const ref to position.
     */
    [[nodiscard]] const glm::vec3 &position() const { return m_position; }

    /**
     * Position reference.
     * @return ref to position.
     */
    glm::vec3 &position() { return m_position; }

    /**
     * Rotations constant reference.
     * @return const ref to rotations.
     */
    [[nodiscard]] const glm::vec3 &rotations() const { return m_rotations; }

    /**
     * Rotations reference.
     * @return ref to rotations.
     */
    glm::vec3 &rotations() { return m_rotations; }

    /**
     * Scale constant reference.
     * @return const ref to scale.
     */
    [[nodiscard]] const glm::vec3 &scale() const { return m_scale; }

    /**
     * Scale reference.
     * @return ref to scale.
     */
    glm::vec3 &scale() { return m_scale; }

    /**
     * Name constant reference.
     * @return const ref to name.
     */
    [[nodiscard]] const std::string &name() const { return m_name; }

    /**
     * Name reference.
     * @return ref to name.
     */
    std::string &name() { return m_name; }

    /**
     * Parent getter.
     * @return parent Composite .
     */
    [[nodiscard]] const Composite *getParent() const;

    /**
     * Parent setter.
     * @param composite - new parent.
     */
    void setParent(Composite *composite);

    core::SettingManager getTransformations();

    void setTransformations(const core::SettingManager &settings);

    virtual void reset() { m_parent = nullptr; }

    virtual void update() {}

    [[nodiscard]] virtual bool isComposite() const = 0;

   private:
    [[nodiscard]] glm::mat4 calculateModel() const;

    [[nodiscard]] glm::mat4 calculateNormalizedModel() const;

    [[nodiscard]] glm::mat4 calculateScaleMat() const;

    [[nodiscard]] glm::mat4 calculateRotationMat() const;

    [[nodiscard]] glm::mat4 calculateTranslationMat() const;

    glm::vec3 m_position{0.f};
    glm::vec3 m_rotations{0.f};
    glm::vec3 m_scale{1.f};

    bool m_selected{false};

    Composite *m_parent;
    std::string m_name;

    static int m_nrDrawables;
};
}  // namespace engine
}  // namespace daft