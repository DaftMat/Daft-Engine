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
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Accepts a DrawableVisitor.
     * @param visitor - visitor.
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Resets the object.
     */
    void reset() override;

    /**
     * Updates the object.
     * Resets all the meshes' VAO.
     */
    void update() override;

    /**
     * Subdivides triangles of each meshes in 4 new triangles.
     */
    void subdivide();

    /**
     * Tests if this is a Composite .
     * @return false.
     */
    [[nodiscard]] bool isComposite() const override { return false; }

    /**
     * Tests if this is an Object .
     * @return true.
     */
    [[nodiscard]] bool isObject() const override { return true; }

    /**
     * Tests if this is a Light .
     * @return false.
     */
    [[nodiscard]] bool isLight() const override { return false; }

   protected:
    virtual void applyUpdate() {}

    std::vector<MeshObject> m_meshObjects;

   private:
    void _render();

    static int m_nrObject;
};
}  // namespace daft::engine