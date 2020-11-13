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
    /**
     * Standard constructor.
     * @param cubeSize - size of a cube sample.
     * @param isoLevel - iso level of the caves' surface.
     * @param parent - parent Composite .
     * @param name - name of the caves.
     */
    explicit Caves(float cubeSize = 0.2f, float isoLevel = 1.f, Composite *parent = nullptr,
                   std::string name = "Caves" + std::to_string(m_nrCaves++));

    /**
     * Default destructor.
     */
    ~Caves() override = default;

    /**
     * Default move constructor.
     */
    Caves(Caves &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
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

    /**
     * Grid size setter.
     * @param cs - new grid size.
     */
    void setGridSize(glm::vec3 cs);

    /**
     * Grid size getter.
     * @return grid size.
     */
    [[nodiscard]] glm::vec3 gridSize() const { return m_marchingCube.gridSize(); }

    /**
     * Cube size setter.
     * @param cs - new cube size.
     */
    void setCubeSize(float cs);

    /**
     * Cube size getter.
     * @return cube size.
     */
    [[nodiscard]] float cubeSize() const { return m_marchingCube.cubeSize(); }

    /**
     * Iso level setter.
     * @param il - new iso level.
     */
    void setIsoLevel(float il);

    /**
     * Iso level getter.
     * @return iso level.
     */
    [[nodiscard]] float isoLevel() const { return m_marchingCube.isoLevel(); }

    /**
     * Seed setter
     * @param s - new seed.
     */
    void setSeed(int s);

    /**
     * Seed getter.
     * @return seed.
     */
    [[nodiscard]] int seed() const { return m_seed; }

    /**
     * Scale setter.
     * @param s - new scale.
     */
    void setScale(float s);

    /**
     * Scale getter.
     * @return scale.
     */
    [[nodiscard]] float getScale() const { return m_noise.scale(); }

    /**
     * Octaves setter.
     * @param o - new octaves
     */
    void setOctaves(int o);

    /**
     * Octaves getter.
     * @return octaves
     */
    [[nodiscard]] int octaves() const { return m_noise.octaves(); }

    /**
     * Persistence setter.
     * @param p - new persistence.
     */
    void setPersistence(float p);

    /**
     * Persistence getter.
     * @return persistence.
     */
    [[nodiscard]] float persistence() const { return m_noise.persistence(); }

    /**
     * Lacunarity setter.
     * @param l - new lacunarity
     */
    void setLacunarity(float l);

    /**
     * Lacunarity getter.
     * @return lacunarity.
     */
    [[nodiscard]] float lacunarity() const { return m_noise.lacunarity(); }

    /**
     * Offset setter.
     * @param o - new offset.
     */
    void setOffset(glm::vec3 o);

    /**
     * Offset getter.
     * @return offset.
     */
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