//
// Created by mathis on 18/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>

#include "BSplineBase.hpp"

namespace daft::core {
class ENGINE_API BSpline2DBase : public core::NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param controlPoints - list of points that define the control polygon.
     * @param base - base of the spline.
     */
    explicit BSpline2DBase(const std::vector<std::vector<glm::vec3>> &controlPoints = {}, int base = 2);

    /**
     * Default destructor.
     */
    ~BSpline2DBase() = default;

    /**
     * Default move constructor.
     */
    BSpline2DBase(BSpline2DBase &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    BSpline2DBase &operator=(BSpline2DBase &&) noexcept = default;

    /**
     * Base const getter.
     * @return base of the spline.
     */
    [[nodiscard]] int base() const { return m_base; }

    /**
     * Base setter.
     * @param b - new base.
     */
    void setBase(int b);

    /**
     * Resets the nodal vectors of the inner splines
     */
    void resetNodalVectors() {
        for (auto &s : m_uSplines) s.resetNodalVector();
    }

    /**
     * Get u nodal vector.
     */
    [[nodiscard]] const std::vector<float> &uNodalVector() const { return m_uSplines[0].nodalVector(); }

    /**
     * Get v nodal vector.
     */
    [[nodiscard]] std::vector<float> vNodalVector() const;

    /**
     * Director splines getter.
     * @return directors.
     */
    [[nodiscard]] const std::vector<BSplineBase> &USplines() const { return m_uSplines; }

    /**
     * Width const getter (number of control points).
     * @return width of the spline.
     */
    [[nodiscard]] int width() const { return m_uSplines[0].controlPoints().size(); }

    /**
     * Height const getter (numger of control points).
     * @return height of the spline.
     */
    [[nodiscard]] int height() const { return m_uSplines.size(); }

    /**
     * Evaluates the 3D position of the spline at the (u,v) coordinates.
     */
    [[nodiscard]] glm::vec3 eval(float u, float v) const;

   private:
    std::vector<BSplineBase> m_uSplines;
    int m_base;
};
}  // namespace daft::core