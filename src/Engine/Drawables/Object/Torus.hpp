//
// Created by mathis on 10/09/2020.
//
#pragma once
#include <API.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API Torus : public Object {
   public:
    explicit Torus(int meridians = 32, int parallels = 16, float innerRadius = 1.f, float outerRadius = 0.5f,
                   Composite *parent = nullptr, std::string name = "Torus" + std::to_string(m_nrTorus++));

    ~Torus() override = default;

    Torus(Torus &&) noexcept = default;

    Torus &operator=(Torus &&) noexcept = default;

    /**
     * Gets the sphere's specific settings as a SettingManager .
     * @return settings.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Settings setter using a SettingManager .
     * @param s - settings.
     */
    void setSettings(const core::SettingManager &s) override;

    [[nodiscard]] int meridians() const { return m_meridians; }

    void setMeridians(int m);

    [[nodiscard]] int parallels() const { return m_parallels; }

    void setParallels(int p);

    [[nodiscard]] float innerRadius() const { return m_innerRadius; }

    void setInnerRadius(float r);

    [[nodiscard]] float outerRadius() const { return m_outerRadius; }

    void setOuterRadius(float r);

    void accept(core::DrawableVisitor *visitor) override;

   protected:
    void applyUpdate() override { createTorus(); }

   private:
    void createTorus();

    int m_meridians{32};
    int m_parallels{16};
    float m_innerRadius{1.f};
    float m_outerRadius{0.5f};

    static int m_nrTorus;
};
}  // namespace daft::engine