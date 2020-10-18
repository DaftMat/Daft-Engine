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
    explicit BSpline2DBase(const std::vector<std::vector<glm::vec3>> &controlPoints = {}, int base = 2);

    ~BSpline2DBase() = default;

    BSpline2DBase(BSpline2DBase &&) noexcept = default;

    BSpline2DBase &operator=(BSpline2DBase &&) noexcept = default;

    [[nodiscard]] int base() const { return m_base; }

    void setBase(int b);

    void resetNodalVectors() {
        for (auto &s : m_uSplines) s.resetNodalVector();
    }

    [[nodiscard]] const std::vector<float> &uNodalVector() const { return m_uSplines[0].nodalVector(); }

    [[nodiscard]] std::vector<float> vNodalVector() const;

    [[nodiscard]] const std::vector<BSplineBase> &USplines() const { return m_uSplines; }

    [[nodiscard]] int width() const { return m_uSplines[0].controlPoints().size(); }

    [[nodiscard]] int height() const { return m_uSplines.size(); }

    [[nodiscard]] glm::vec3 eval(float u, float v) const;

   private:
    std::vector<BSplineBase> m_uSplines;
    int m_base;
};
}  // namespace daft::core