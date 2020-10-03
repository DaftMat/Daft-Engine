//
// Created by mathis on 03/10/2020.
//
#pragma once
#include <API.hpp>

#include "Light.hpp"

namespace daft::engine {
class ENGINE_API DirLight : public Light {
   public:
    explicit DirLight(glm::vec3 dir = {0.f, -1.f, 0.f}, glm::vec3 color = glm::vec3{0.8f}, Composite *parent = nullptr,
                      std::string name = "DirLight" + std::to_string(m_nrDirLight++));

    ~DirLight() override = default;

    DirLight(DirLight &&) noexcept = default;

    DirLight &operator=(DirLight &&) noexcept = default;

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
     * Can't translate a directionnal light.
     * Does nothing.
     * @param t ~~
     */
    void translate(glm::vec3 t) override {}

    /**
     * Ges the direction pointed by the light.
     * @return direction.
     */
    glm::vec3 direction() const { return m_direction; }

    // void applyUpdate() override { createDirLight(); }

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
    Type getType() const override { return Type::SpotLight; }

   private:
    void createDirLight();

    glm::vec3 m_direction;
    glm::vec3 m_baseDirection;

    static int m_nrDirLight;
};
}  // namespace daft::engine