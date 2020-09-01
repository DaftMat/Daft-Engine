//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>
#include <Engine/Drawables/Drawable.hpp>
#include <Engine/Drawables/MeshObject.hpp>

namespace daft::engine {
/**
 * Base 3D object.
 */
class ENGINE_API Object : public Drawable {
   public:
    /**
     * Standard constructor.
     * @param mos - list of mesh objects.
     */
    explicit Object(Composite *parent = nullptr, std::string name = "Object" + std::to_string(m_nrObject++),
                    std::vector<MeshObject> mos = {}) noexcept;

    /**
     * One mesh constructor.
     * @param mo - mesh object.
     */
    explicit Object(Composite *parent, MeshObject mo) noexcept;

    ~Object() noexcept override;

    /**
     * Default move constructor.
     */
    Object(Object &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return reference to this.
     */
    Object &operator=(Object &&) noexcept = default;

    /**
     * Renders the mesh objects.
     */
    void render(const core::ShaderProgram &shader) override;

    /**
     * Accepts a DrawableVisitor.
     * @param visitor - visitor.
     */
    void accept(DrawableVisitor *visitor) override;

    void reset() override;

    void update() override;

    void updateNextFrame() { m_update = true; }

    void subdivide(bool normalsArePositions = false);

    [[nodiscard]] bool isComposite() const override { return false; }

   protected:
    virtual void applyUpdate() {}
    bool m_update;

    std::vector<MeshObject> m_meshObjects;

   private:
    static glm::vec3 computeHalfVertex(const glm::vec3 &a, glm::vec3 &b) { return glm::normalize(a + b); }

    static int m_nrObject;
};
}  // namespace daft::engine