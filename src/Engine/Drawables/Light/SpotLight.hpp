//
// Created by mathis on 30/09/2020.
//
#pragma once
#include <API.hpp>

#include "Light.hpp"

namespace daft::engine {
class ENGINE_API SpotLight : public Light {
   public:
    /**
     * Standard constructor.
     * @param dir - direction of the light.
     * @param intensity - intensity of the light.
     * @param innerCutOff - inner cut off angle of the light.
     * @param outerCutOff - outer cut off angle of the light.
     * @param color - color of the light.
     * @param parent - parent Composite .
     * @param name - name of the light.
     */
    explicit SpotLight(glm::vec3 dir = {0.f, -1.f, 0.f}, float intensity = 1.f, float innerCutOff = 12.5f,
                       float outerCutOff = 15.f, glm::vec3 color = glm::vec3{0.8f}, Composite *parent = nullptr,
                       std::string name = "SpotLight" + std::to_string(m_nrSpotLight++));

    /**
     * Default destructor.
     */
    ~SpotLight() override = default;

    /**
     * Default move constructor.
     */
    SpotLight(SpotLight &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
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

    /**
     * Direction getter.
     * @return direction of the light.
     */
    glm::vec3 direction() const { return m_direction; }

    /**
     * Intensity getter.
     * @return intensity of the light.
     */
    float intensity() const { return m_intensity; }

    /**
     * Intensity setter.
     * @param i - new intensity.
     */
    void setIntensity(float i);

    /**
     * Inner cut off getter.
     * @return inner cut off angle of the light.
     */
    float innerCutOff() const { return m_innerCutOff; }

    /**
     * Inner cut off setter.
     * @param i - new inner cut off.
     */
    void setInnerCutOff(float i);

    /**
     * Outer cut off getter.
     * @return outer cut off angle of the light.
     */
    float outerCutOff() const { return m_outerCutOff; }

    /**
     * Outer cut off setter.
     * @param o - new outer cut off.
     */
    void setOuterCutOff(float o);

    /**
     * Loads this light to a target shader as a uniform struct.
     * @param shader - shader to load the light to.
     * @param index - index of the light in its list.
     */
    void loadToShader(const core::ShaderProgram &shader, int index) const override;

    /**
     * Render the scene to a shadow map.
     * @param root - scene.
     * @param shader - shader to be used.
     * @param screenWidth - width of the original viewport.
     * @param screenHeight - height of the original viewport.
     * @param viewCam - original viewport's camera.
     */
    void renderToLightMap(Composite *root, const core::ShaderProgram &shader, int screenWidth, int screenHeight,
                          const Camera &viewCam) override;

    /**
     * Accepts a DrawableVisitor.
     * @param visitor - visitor.
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return Type::SpotLight .
     */
    Type getType() const override { return Type::SpotLight; }

   protected:
    void applyUpdate() override { createSpotLight(); }

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