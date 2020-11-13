//
// Created by mathis on 17/05/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <memory>
#include <vector>

#include "Perlin.hpp"

namespace daft::core {
/**
 * Uses the same perlin noise several times (octaves) to generate a procedural height map
 */
class ENGINE_API Noise : public NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param scale - scale of the noise.
     * @param octaves - number of octaves.
     * @param persistence - persistences of octaves.
     * @param lacunarity - lacunarity of octaves.
     * @param offset - offset of the noise.
     * @param perlin - base perlin.
     */
    explicit Noise(float scale = 1.f, int octaves = 5, float persistence = 0.5f, float lacunarity = 2.f,
                   const glm::vec3 &offset = glm::vec3{1000000.f},
                   std::unique_ptr<Perlin> perlin = std::make_unique<Perlin>(2020, 255));

    /**
     * Generates a height map based on perlin noise
     * @return 2D height map as a 1D array.
     */
    std::vector<float> generate();

    /**
     * Return the value of the stacked perlin noises given a 3D point.
     * @param p - 3D point.
     * @return perlin noises' iso level.
     */
    float eval(glm::vec3 p);

    /**
     * Scale ref getter.
     * @return scale of the noise.
     */
    float &scale() { return m_scale; }

    /**
     * Scale getter.
     * @return scale of the noise.
     */
    [[nodiscard]] float scale() const { return m_scale; }

    /**
     * Octaves ref getter.
     * @return octaves of the noise.
     */
    int &octaves() { return m_octaves; }

    /**
     * Octaves getter.
     * @return octaves of the noise.
     */
    [[nodiscard]] int octaves() const { return m_octaves; }

    /**
     * Persistence ref getter.
     * @return persistence of the octaves.
     */
    float &persistence() { return m_persistence; }

    /**
     * Persistence getter.
     * @return persistence of the octaves.
     */
    [[nodiscard]] float persistence() const { return m_persistence; }

    /**
     * Lacunarity ref getter.
     * @return lacunarity of the octaves.
     */
    float &lacunarity() { return m_lacunarity; }

    /**
     * Lacunarity getter.
     * @return lacunarity of the octaves.
     */
    [[nodiscard]] float lacunarity() const { return m_lacunarity; }

    /**
     * x offset ref getter.
     * @return x offset.
     */
    float &xOffset() { return m_xOffset; }

    /**
     * x offset getter.
     * @return x offset.
     */
    [[nodiscard]] float xOffset() const { return m_xOffset; }

    /**
     * y offset ref getter.
     * @return y offset.
     */
    float &yOffset() { return m_yOffset; }

    /**
     * y offset getter.
     * @return y offset.
     */
    [[nodiscard]] float yOffset() const { return m_yOffset; }

    /**
     * z offset ref getter.
     * @return z offset.
     */
    float &zOffset() { return m_zOffset; }

    /**
     * z offset getter.
     * @return z offset.
     */
    [[nodiscard]] float zOffset() const { return m_zOffset; }

    /**
     * Perlin base setter.
     * @param perlin - new perlin.
     */
    void setPerlin(std::unique_ptr<Perlin> perlin) { m_perlin = std::move(perlin); }

    /**
     * Perlin getter.
     * @return perlin.
     */
    [[nodiscard]] const Perlin &perlin() const { return *m_perlin; }

    /**
     * Perlin ref getter.
     * @return perlin.
     */
    Perlin &perlin() { return *m_perlin; }

   private:
    static float invlerp(float a, float b, float v) { return (v - a) / (b - a); }

    float m_scale;
    int m_octaves;
    float m_persistence, m_lacunarity;
    float m_xOffset, m_yOffset, m_zOffset;
    std::unique_ptr<Perlin> m_perlin{nullptr};
};
}  // namespace daft::core
