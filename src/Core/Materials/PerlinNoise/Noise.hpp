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
class ENGINE_API Noise : public NonCopyable {
   public:
    explicit Noise(float scale = 1.f, int octaves = 5, float persistence = 0.5f, float lacunarity = 2.f,
                   const glm::vec3 &offset = glm::vec3{0.f},
                   std::unique_ptr<Perlin> perlin = std::make_unique<Perlin>(2020, 255));

    std::vector<float> generate();

    float eval(glm::vec3 p);

    float &scale() { return m_scale; }

    [[nodiscard]] float scale() const { return m_scale; }

    int &octaves() { return m_octaves; }

    [[nodiscard]] int octaves() const { return m_octaves; }

    float &persistence() { return m_persistence; }

    [[nodiscard]] float persistence() const { return m_persistence; }

    float &lacunarity() { return m_lacunarity; }

    [[nodiscard]] float lacunarity() const { return m_lacunarity; }

    float &xOffset() { return m_xOffset; }

    [[nodiscard]] float xOffset() const { return m_xOffset; }

    float &yOffset() { return m_yOffset; }

    [[nodiscard]] float yOffset() const { return m_yOffset; }

    float &zOffset() { return m_zOffset; }

    [[nodiscard]] float zOffset() const { return m_zOffset; }

    void setPerlin(std::unique_ptr<Perlin> perlin) { m_perlin = std::move(perlin); }

    [[nodiscard]] const Perlin &perlin() const { return *m_perlin; }

   private:
    static float invlerp(float a, float b, float v) { return (v - a) / (b - a); }

    float m_scale;
    int m_octaves;
    float m_persistence, m_lacunarity;
    float m_xOffset, m_yOffset, m_zOffset;
    std::unique_ptr<Perlin> m_perlin{nullptr};
};
}  // namespace daft::core
