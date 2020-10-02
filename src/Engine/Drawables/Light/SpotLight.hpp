//
// Created by mathis on 30/09/2020.
//
#pragma once
#include <API.hpp>

#include "Light.hpp"

namespace daft::engine {
class ENGINE_API SpotLight : public Light {
   public:
    explicit SpotLight(glm::vec3 dir = {0.f, -1.f, 0.f}, float intensity = 1.f, float innerCutOff = 12.5f,
                       float outerCutOff = 15.f, glm::vec3 color = glm::vec3{0.8f}, Composite *parent = nullptr,
                       std::string name = "SpotLight" + std::to_string(m_nrSpotLight++));

    ~SpotLight() override = default;

    SpotLight(SpotLight &&) noexcept = default;

    SpotLight &operator=(SpotLight &&) noexcept = default;

    /**
     * Gets the drawable's specific settings as a SettingManager .
     * @return settings.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Settings setter using a SettingManager .
     * @param s - settings.
     */
    void setSettings(const core::SettingManager &s) override;

    /**
     * Transformations setter using a SettingManager .
     * @param t - transformations.
     */
    void setTransformations(const core::SettingManager &t) override;

    glm::vec3 direction() const { return m_direction; }

    float intensity() const { return m_intensity; }

    void setIntensity(float i);

    float innerCutOff() const { return m_innerCutOff; }

    void setInnerCutOff(float i);

    float outerCutOff() const { return m_outerCutOff; }

    void setOuterCutOff(float o);

    void applyUpdate() override { createSpotLight(); }

    /**
     * Loads this light to a target shader as a uniform struct.
     * @param shader - shader to load the light to.
     * @param index - index of the light in its list.
     */
    void loadToShader(const core::ShaderProgram &shader, int index) const override;

    /**
     * Accepts a DrawableVisitor.
     * @param visitor - visitor.
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return Type::SpotLight .
     */
    Type getType() override { return Type::SpotLight; }

   private:
    void createSpotLight();

    glm::vec3 m_direction;
    glm::vec3 m_baseDirection;
    float m_intensity;
    float m_innerCutOff;
    float m_outerCutOff;

    static int m_nrSpotLight;
};
}  // namespace daft::engine