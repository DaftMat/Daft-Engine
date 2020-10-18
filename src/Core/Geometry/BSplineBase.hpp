//
// Created by mathis on 24/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/Types.hpp>
#include <vector>

namespace daft::core {
/**
 * A class that calculates the position of the BSpline at any value of u.
 */
class ENGINE_API BSplineBase {
   public:
    /**
     * Constructor.
     * @param controlPoints - control polygon of the BSpline (1D).
     * @param base - base of the B-Spline
     */
    explicit BSplineBase(std::vector<glm::vec3> controlPoints = {}, int base = 2);

    /**
     * Evaluates the position of the B-Spline.
     * @param u - position in 1D world
     * @return - 3D position of the B-Spline.
     */
    [[nodiscard]] glm::vec3 eval(float u) const;

    /**
     * Control points constant reference.
     * @return const ref to controlPoints.
     */
    [[nodiscard]] const auto &controlPoints() const { return m_controlPoints; }

    /**
     * Control point reference.
     * @return ref to controlPoints.
     */
    auto &controlPoints() { return m_controlPoints; }

    /**
     * Nodal vector constant reference.
     * @return const ref to nodalVector.
     */
    [[nodiscard]] const auto &nodalVector() const { return m_nodalVector; }

    /**
     * Nodal vector reference.
     * @return ref to nodalVector.
     */
    auto &nodalVector() { return m_nodalVector; }

    /**
     * Base getter.
     * @return base.
     */
    [[nodiscard]] int base() const { return m_base; }

    /**
     * Base reference.
     * @return reference to base.
     */
    int &base() { return m_base; }

    /**
     * Adds a point to the control points list.
     * @param p - point to add.
     */
    void addPoint(glm::vec3 p = glm::vec3{0.f}) { m_controlPoints.push_back(p); }

    void resetNodalVector();

   private:
    std::vector<glm::vec3> m_controlPoints;
    std::vector<float> m_nodalVector;
    int m_base{2};
};
}  // namespace daft::core