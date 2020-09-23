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
    explicit Cube(float radius = 1.f, int resolution = 8, Composite *parent = nullptr,
                  std::string name = "Cube" + std::to_string(m_nrCube++));

    ~Cube() override = default;

    Cube(Cube &&) noexcept = default;

    Cube &operator=(Cube &&) noexcept = default;

    [[nodiscard]] core::SettingManager getSettings() const override;

    void setSettings(const core::SettingManager &s) override;

    [[nodiscard]] float radius() const { return m_radius; }

    void setRadius(float r);

    [[nodiscard]] int resolution() const { return m_resolution; }

    void setResolution(int r);

    void accept(core::DrawableVisitor *visitor) override { visitor->visit(this); }

   protected:
    void applyUpdate() override;

   private:
    void createCube();

    float m_radius{1.f};
    int m_resolution{8};

    static int m_nrCube;
};
}  // namespace daft::engine