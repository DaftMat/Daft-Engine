//
// Created by mathis on 24/09/2020.
//
#include "BSplineBase.hpp"

namespace daft::core {
BSplineBase::BSplineBase(std::vector<glm::vec3> controlPoints, int base)
    : m_controlPoints{std::move(controlPoints)}, m_base{base} {}

glm::vec3 BSplineBase::eval(float u) const {
    /// find pTemp
    int k = m_base + 1;
    int dec = 0, i = k;
    while (u > m_modalVector[i++]) dec++;

    std::vector<glm::vec3> pTemp;
    for (int j = dec; j < dec + k; ++j) pTemp.push_back(m_controlPoints[j]);

    /// calculate B-Spline point at u
    for (int h = 0; h < m_base; ++h) {
        for (int j = 0; j < k - 1; ++j) {
            float u1 = m_modalVector[dec + k + j];
            float u2 = m_modalVector[dec + 1 + j];
            float div = u1 - u2;
            pTemp[j] = (u1 - u) / div * pTemp[j] + (u - u2) / div * pTemp[j + 1];
        }
        ++dec;
        --k;
    }
    return pTemp[0];
}
}  // namespace daft::core