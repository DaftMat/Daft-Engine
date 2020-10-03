//
// Created by daftmat on 23/09/2020.
//

#pragma once
#include <API.hpp>
#include <Core/Geometry/BSplineBase.hpp>

#include "Object.hpp"

namespace daft::engine {
/**
 * An object that uses BSplineBase to draw a B-Spline
 */
class ENGINE_API BSpline : public Object {
   public:
    /**
     * Constructor.
     * @param controlPoints - control polygon, as a list of points.
     * @param base - base of the spline.
     * @param steps - number of point that compose the spline.
     * @param parent - parent Composite.
     * @param name - name of the object.
     */
    explicit BSpline(std::vector<glm::vec3> controlPoints = {}, int base = 2, float steps = 100.f,
                     Composite *parent = nullptr, std::string name = "BSpline" + std::to_string(m_nrBSpline));

    /**
     * Destructor.
     */
    ~BSpline() override = default;

    /**
     * Default move constructor.
     */
    BSpline(BSpline &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    BSpline &operator=(BSpline &&) noexcept = default;

    /**
     * Render the triangles related to the spline (e.g. tensor)
     * @param shader - shader to render with.
     */
    void render(const core::ShaderProgram &shader) override {}

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
     * Control polygon getter.
     * @return the list of points that are part of the control polygon of the b-spline.
     */
    [[nodiscard]] const auto &points() const { return m_spline.controlPoints(); }

    /**
     * Adds a point to the control polygon.
     * @param p - point to add.
     */
    void addPoint(glm::vec3 p = glm::vec3{0.f});

    /**
     * Gets the currently selected point.
     * @return selected point in the control polygon.
     */
    [[nodiscard]] glm::vec3 getSelectedPoint() const;

    /**
     * Gets the currently selected point's index.
     * @return selection as an index.
     */
    [[nodiscard]] int getSelectedIndex() const { return m_selectedPoint; }

    /**
     * Updates the currently selected point.
     * @param p - new position of the selected point.
     */
    void setSelectedPoint(int p) { m_selectedPoint = p < int(points().size()) ? p : -1; }

    /**
     * Accepts a visitor.
     * @param visitor - visitor to accept.
     */
    void accept(core::DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return nothing.
     */
    Type getType() const override { return Type::BSpline; }

   protected:
    void applyUpdate() override { createBSpline(); }

   private:
    void createBSpline();

    core::BSplineBase m_spline;
    float m_steps{100.f};
    int m_selectedPoint{-1};

    static int m_nrBSpline;
};
}  // namespace daft::engine
