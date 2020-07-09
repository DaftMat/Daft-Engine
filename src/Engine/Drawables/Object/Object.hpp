//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>
#include <Engine/Drawables/Drawable.hpp>

namespace daft::engine::objects {
class MeshObject;

/**
 * Base 3D object.
 */
class ENGINE_API Object : public Drawable {
   public:
    /**
     * Standard constructor.
     * @param mos - list of mesh objects.
     */
    explicit Object(std::vector<MeshObject> mos = {}) noexcept;

    /**
     * One mesh constructor.
     * @param mo - mesh object.
     */
    explicit Object(MeshObject mo) noexcept;

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
    void render() override;

    /**
     * Accepts a DrawableVisitor.
     * @param visitor - visitor.
     */
    inline void accept(DrawableVisitor *visitor) override;

   private:
    std::vector<MeshObject> m_meshObjects;
};
}  // namespace daft::engine::objects