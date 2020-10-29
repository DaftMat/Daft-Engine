//
// Created by mathis on 28/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/MarchingCube.hpp>
#include <Core/Materials/PerlinNoise/Noise.hpp>

#include "Object.hpp"

namespace daft::engine {
class ENGINE_API Caves : public Object {
   public:
    explicit Caves(float cubeSize = 0.2f, float isoLevel = 1.f, Composite *parent = nullptr,
                   std::string name = "Caves" + std::to_string(m_nrCaves++));

    ~Caves() override = default;

    Caves(Caves &&) noexcept = default;

    Caves &operator=(Caves &&) noexcept = default;

    /**
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Gets settings as a SettingManager.
     * @return settings of the metaballs.
     */
    [[nodiscard]] core::SettingManager getSettings() const override;

    /**
     * Sets the settings using a SettingManager.
     * @param s - updated settings.
     */
    void setSettings(const core::SettingManager &s) override;

    void setGridSize(glm::vec3 cs);

    [[nodiscard]] glm::vec3 gridSize() const { return m_marchingCube.gridSize(); }

    void setCubeSize(float cs);

    [[nodiscard]] float cubeSize() const { return m_marchingCube.cubeSize(); }

    void setIsoLevel(float il);

    [[nodiscard]] float isoLevel() const { return m_marchingCube.isoLevel(); }

    void setSeed(int s);

    [[nodiscard]] int seed() const { return m_seed; }

    void setScale(float s);

    [[nodiscard]] float getScale() const { return m_noise.scale(); }

    void setOctaves(int o);

    [[nodiscard]] int octaves() const { return m_noise.octaves(); }

    void setPersistence(float p);

    [[nodiscard]] float persistence() const { return m_noise.persistence(); }

    void setLacunarity(float l);

    [[nodiscard]] float lacunarity() const { return m_noise.lacunarity(); }

    void setOffset(glm::vec3 o);

    [[nodiscard]] glm::vec3 offset() const {
        return glm::vec3{m_noise.xOffset(), m_noise.yOffset(), m_noise.zOffset()};
    }

    /**
     * Accepts a visitor.
     * @param visitor - visitor to accept.
     */
    void accept(core::DrawableVisitor *visitor) override;

    /**
     * Gets the type of drawable.
     * @return nothing.
     */
    [[nodiscard]] Type getType() const override { return Type::Caves; }

   protected:
    void applyUpdate() override { createPerlin3D(); }

   private:
    void createPerlin3D();

    core::MarchingCube m_marchingCube;
    core::Noise m_noise;
    int m_seed{2020};

    std::function<float(glm::vec3)> m_isoSurface;

    static int m_nrCaves;
};
}  // namespace daft::engine