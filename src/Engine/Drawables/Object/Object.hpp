//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>
#include <Engine/Drawables/Drawable.hpp>
#include <Engine/Drawables/MeshObject.hpp>

namespace daft::engine::objects {
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

    ~Object() noexcept;

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
    void accept(const DrawableVisitor *visitor) override;

    void reset() override;

   private:
    std::vector<MeshObject> m_meshObjects;

    static int m_nrObject;
};
}  // namespace daft::engine::objects