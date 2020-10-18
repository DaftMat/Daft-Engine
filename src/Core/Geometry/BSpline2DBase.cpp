//
// Created by mathis on 18/10/2020.
//
#include "BSpline2DBase.hpp"

namespace daft::core {
BSpline2DBase::BSpline2DBase(const std::vector<std::vector<glm::vec3>> &controlPoints, int base) : m_base{base} {
    for (auto cp : controlPoints) {
        m_uSplines.emplace_back(std::move(cp), base);
    }
}

void BSpline2DBase::setBase(int b) {
    m_base = b;
    for (auto &s : m_uSplines) {
        s.base() = b;
    }
}

std::vector<float> BSpline2DBase::vNodalVector() const {
    std::vector<float> nv;
    for (int i = 0; i < m_base + int(m_uSplines.size()) + 1; ++i) nv.push_back(float(i));
    return nv;
}

glm::vec3 BSpline2DBase::eval(float u, float v) const {
    std::vector<glm::vec3> vControlPoints;
    for (auto &uSpline : m_uSplines) vControlPoints.push_back(uSpline.eval(u));
    BSplineBase vSpline{std::move(vControlPoints), m_base};
    vSpline.resetNodalVector();
    return vSpline.eval(v);
}
}  // namespace daft::core
