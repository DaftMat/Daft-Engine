//
// Created by mathis on 28/11/2020.
//
#pragma once
#include <API.hpp>

#include "Light.hpp"

namespace daft::engine {
class ENGINE_API QuadLight : public Light {
   public:
    /**
     * Default/standard constructor.
     * @param mesh - line mesh that represents the light.
     * @param color - color emitted by the light.
     */
    explicit QuadLight(glm::vec3 position = glm::vec3{0.f}, glm::vec3 xdir = {1.f, 0.f, 0.f},
                       glm::vec3 ydir = {0.f, 1.f, 0.f}, glm::vec2 size = {1.f, 1.f}, glm::vec3 color = glm::vec3{1.f},
                       float intensity = 1.f, Composite *parent = nullptr,
                       std::string name = "QuadLight" + std::to_string(m_nrQuadLight++))
        : Light{color, parent, std::move(name)},
          m_posBase{position},
          m_xDir{xdir},
          m_yDir{ydir},
          m_xDirBase{xdir},
          m_yDirBase{ydir},
          m_width{size.x},
          m_height{size.y},
          m_intensity{intensity} {
        this->position() = position;
        m_isAreaLight = true;
        createQuadLight();
    }

    /**
     * Destructor.
     */
    ~QuadLight() override = default;

    /**
     * Default move constructor.
     */
    QuadLight(QuadLight &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    QuadLight &operator=(QuadLight &&) noexcept = default;

    void render(const core::ShaderProgram &shader) override;

    /**
     * Gets the quad light's specific settings as a SettingManager .
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

    float width() const { return m_width; }

    void setWidth(float w);

    float height() const { return m_height; }

    void setHeight(float h);

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
    Type getType() const override { return Type::QuadLight; }

    void update() override { createQuadLight(); }

   private:
    std::vector<glm::vec3> points() const;
    std::vector<glm::vec3> transformedPoints() const;

    void createQuadLight();

    glm::vec3 m_posBase;
    glm::vec3 m_xDir;
    glm::vec3 m_yDir;
    glm::vec3 m_xDirBase;
    glm::vec3 m_yDirBase;
    float m_width;
    float m_height;
    float m_intensity;

    static int m_nrQuadLight;
};
}  // namespace daft::engine