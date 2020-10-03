//
// Created by daftmat on 23/09/2020.
//

#pragma once
#include <API.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

#include "Object.hpp"

namespace daft::engine {
/**
 * cube class.
 */
class ENGINE_API Cube : public Object {
   public:
    /**
     * Constructor.
     * @param radius - radius of the cube (edges size / 2).
     * @param resolution - resolution of the cube (number of triangles per edge)
     * @param parent - parent Composite.
     * @param name - name of the object.
     */
    explicit Cube(float radius = 1.f, int resolution = 8, Composite *parent = nullptr,
                  std::string name = "Cube" + std::to_string(m_nrCube++));

    /**
     * Default destructor.
     */
    ~Cube() override = default;

    /**
     * Default move constructor.
     */
    Cube(Cube &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Cube &operator=(Cube &&) noexcept = default;

    /**
     * Gets the settings of the cube as a SettingManager .
     * @return settings of the cube.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Sets the settings of the cube using a SettingManager .
     * @param s - new settings of the cube.
     */
    void setSettings(const core::SettingManager &s) override;

    /**
     * Radius getter.
     * @return radius of the cube.
     */
    [[nodiscard]] float radius() const { return m_radius; }

    /**
     * Radius setter.
     * @param r - new radius.
     */
    void setRadius(float r);

    /**
     * Resolution getter.
     * @return resolution of the cube.
     */
    [[nodiscard]] int resolution() const { return m_resolution; }

    /**
     * Resolution setter.
     * @param r - new resolution.
     */
    void setResolution(int r);

    /**
     * Accepts a visitor
     * @param visitor - visitor to accept.
     */
    void accept(core::DrawableVisitor *visitor) override { visitor->visit(this); }

    /**
     * Gets the type of drawable.
     * @return Type::Cube .
     */
    Type getType() const override { return Type::Cube; }

   protected:
    void applyUpdate() override;

   private:
    void createCube();

    float m_radius{1.f};
    int m_resolution{8};

    static int m_nrCube;
};
}  // namespace daft::engine