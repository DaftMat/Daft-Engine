//
// Created by mathis on 11/09/2020.
//
#pragma once
#include <API.hpp>

#include "Light.hpp"

namespace daft::engine {
class ENGINE_API PointLight : public Light {
   public:
    /**
     * Standard constructor.
     * @param intensity - light's intensity.
     * @param name - light's name.
     * @param parent - Composite holding this light.
     */
    explicit PointLight(float intensity = 1.f, glm::vec3 color = glm::vec3{0.8f}, Composite *parent = nullptr,
                        std::string name = "PointLight" + std::to_string(m_nrPointLights++));

    /**
     * Default destructor.
     */
    ~PointLight() override = default;

    /**
     * Default move constructor.
     */
    PointLight(PointLight &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    PointLight &operator=(PointLight &&) noexcept = default;

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

    /**
     * Intensity getter.
     * @return intensity.
     */
    [[nodiscard]] float intensity() const { return m_intensity; }

    /**
     * Intensity ref getter.
     * @return ref to intensity.
     */
    float &intensity() { return m_intensity; }

    /**
     * No rotation possible for a point light.
     * Does nothing.
     */
    void rotate(glm::vec3 r) override {}

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
     * @return Type::PointLight .
     */
    Type getType() const override { return Type::PointLight; }

   private:
    void createPointLight();

    float m_intensity;

    static int m_nrPointLights;
};
}  // namespace daft::engine