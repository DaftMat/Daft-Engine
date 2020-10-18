//
// Created by mathis on 18/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/BSpline2DBase.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API BSpline2D : public Object {
   public:
    explicit BSpline2D(const std::vector<std::vector<glm::vec3>> &controlPoints = {}, int base = 2, float steps = 100.f,
                       Composite *parent = nullptr, std::string name = "BSpline" + std::to_string(m_nrBSpline2D));

    ~BSpline2D() override = default;

    BSpline2D(BSpline2D &&) noexcept = default;

    BSpline2D &operator=(BSpline2D &&) noexcept = default;

    /**
     * Renders the edges and the control polygons of the b-spline.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Gets settings as a SettingManager.
     * @return settings of the b-spline.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Sets the settings using a SettingManager.
     * @param s - updated settings.
     */
    void setSettings(const core::SettingManager &s) override;

    /**
     * B-Spline's base getter.
     * @return base of the b-spline.
     */
    [[nodiscard]] int base() const { return m_spline.base(); }

    /**
     * B-Spline's base setter.
     * @param b - new base.
     */
    void setBase(int b);

    /**
     * Number of points getter.
     * @return number of points (steps) in the resulting b-spline.
     */
    [[nodiscard]] float steps() const { return m_steps; }

    /**
     * Number of points setter.
     * @param s - new number of points (steps) in the resulting b-spline.
     */
    void setSteps(float s);

    /**
     * Gets the type of drawable.
     * @return nothing.
     */
    [[nodiscard]] Type getType() const override { return Type::BSpline2D; }

    void accept(core::DrawableVisitor *visitor) override;

   protected:
    void applyUpdate() override { create2DBSpline(); }

   private:
    void create2DBSpline();

    core::BSpline2DBase m_spline;
    float m_steps;

    static int m_nrBSpline2D;
};
}  // namespace daft::engine