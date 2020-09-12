//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Materials/SettingManager.hpp>
#include <Core/Rendering/ShaderProgram.hpp>
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

    /// All type of drawables (for creation)
    enum class Type {
        /// Objects
        Sphere,
        Cube,
        Cylinder,
        Torus,
        /// Lights
        PointLight,
        DirLight,
        SpotLight,
        /// Composite
        Group,
        /// No type
        None
    };

    /**
     * Standard constructor.
     * @param parent
     */
    explicit Drawable(Composite *parent = nullptr,
                      std::string name = "Drawable" + std::to_string(m_nrDrawables++)) noexcept;

    /**
     * Default destructor.
     */
    virtual ~Drawable() noexcept = default;

    /**
     * Default move constructor.
     */
    Drawable(Drawable &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Drawable &operator=(Drawable &&) noexcept = default;

    /**
     * renders the inner geometry.
     * @param shader - shader to render with.
     */
    virtual void render(const core::ShaderProgram &shader) = 0;

    /**
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    virtual void renderEdges(const core::ShaderProgram &shader) = 0;

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
     * Applies a translation to the drawable.
     * @param t - translation to apply.
     */
    virtual void translate(glm::vec3 t) { m_position += t; }

    /**
     * Applies a rotation to the drawable.
     * @param r - rotation to apply.
     */
    virtual void rotate(glm::vec3 r) { m_rotations += r; }

    /**
     * Re-scales the drawable.
     * @param s - new scale of the drawble.
     */
    virtual void rescale(glm::vec3 s) { m_scale = s; }

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
     * Utils function to remove something from a Composite .
     * @param name - name of the drawable to remove.
     * @return true is the drawable has the right name so it can be deleted from its parent.
     */
    virtual bool remove(const std::string &name) { return name == m_name; }

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
     * Gets the transformations as a SettingManager .
     * @return transformations.
     */
    virtual core::SettingManager getTransformations();

    /**
     * Transformations setter using a SettingManager .
     * @param t - transformations.
     */
    virtual void setTransformations(const core::SettingManager &t);

    /**
     * Gets the drawable's specific settings as a SettingManager .
     * @return settings.
     */
    [[nodiscard]] virtual core::SettingManager getSettings() const { return core::SettingManager{}; }

    /**
     * Settings setter using a SettingManager .
     * @param s - settings.
     */
    virtual void setSettings(const core::SettingManager &s) {}

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

    /**
     * Resets the drawable.
     */
    virtual void reset() { m_parent = nullptr; }

    /**
     * updates the drawable (rebuild its vao for an Object ).
     */
    virtual void update() {}

    /**
     * Tests if this is a Composite .
     * to be overridden.
     * @return true if this is a composite, false otherwise.
     */
    [[nodiscard]] virtual bool isComposite() const = 0;

    /**
     * Tests if this is an Object .
     * to be overridden.
     * @return true if this is an object, false otherwise.
     */
    [[nodiscard]] virtual bool isObject() const = 0;

    /**
     * Tests if this is a Light .
     * to be overridden.
     * @return true if this is a light, false otherwise.
     */
    [[nodiscard]] virtual bool isLight() const = 0;

    /**
     * Selects the object.
     */
    void select() { m_isSelected = true; }

    /**
     * Unselect the object.
     */
    void unselect() { m_isSelected = false; }

    /**
     * Tests if this is selected.
     * @return true if this is the current selection.
     */
    [[nodiscard]] bool selected() const { return m_isSelected; }

    /**
     * Tells this object to update on the next frame.
     */
    void updateNextFrame() { m_update = true; }

   protected:
    bool m_update;

   private:
    [[nodiscard]] glm::mat4 calculateModel() const;
    [[nodiscard]] glm::mat4 calculateNormalizedModel() const;
    [[nodiscard]] glm::mat4 calculateScaleMat() const;
    [[nodiscard]] glm::mat4 calculateRotationMat() const;
    [[nodiscard]] glm::mat4 calculateTranslationMat() const;

    glm::vec3 m_position{0.f};
    glm::vec3 m_rotations{0.f};
    glm::vec3 m_scale{1.f};

    Composite *m_parent;
    std::string m_name;

    bool m_isSelected{false};

    static int m_nrDrawables;
};
}  // namespace engine
}  // namespace daft