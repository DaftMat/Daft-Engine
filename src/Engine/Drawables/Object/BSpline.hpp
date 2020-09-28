//
// Created by daftmat on 23/09/2020.
//

#pragma once
#include <API.hpp>
#include <Core/Geometry/BSplineBase.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API BSpline : public Object {
   public:
    explicit BSpline(std::vector<glm::vec3> controlPoints = {}, int base = 2, float steps = 100.f,
                     Composite *parent = nullptr, std::string name = "BSpline" + std::to_string(m_nrBSpline));

    ~BSpline() override = default;

    BSpline(BSpline &&) noexcept = default;

    BSpline &operator=(BSpline &&) noexcept = default;

    void render(const core::ShaderProgram &shader) override {}

    void renderEdges(const core::ShaderProgram &shader) override;

    [[nodiscard]] core::SettingManager getSettings() const override;

    void setSettings(const core::SettingManager &s) override;

    [[nodiscard]] int base() const { return m_spline.base(); }

    void setBase(int b);

    [[nodiscard]] float steps() const { return m_steps; }

    void setSteps(float s);

    void addPoint(glm::vec3 p = glm::vec3{0.f});

    void accept(core::DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return nothing.
     */
    Type getType() override { return Type::BSpline; }

   protected:
    void applyUpdate() override { createBSpline(); }

   private:
    void createBSpline();

    core::BSplineBase m_spline;
    float m_steps{100.f};

    static int m_nrBSpline;
};
}  // namespace daft::engine
