//
// Created by mathis on 17/05/2020.
//

#include "Noise.hpp"

#include <Core/Random.hpp>

namespace daft::core {
Noise::Noise(float scale, int octaves, float persistence, float lacunarity, const glm::vec3 &offset,
             std::unique_ptr<Perlin> perlin)
    : m_scale{scale},
      m_octaves{octaves},
      m_persistence{persistence},
      m_lacunarity{lacunarity},
      m_xOffset{offset.x},
      m_yOffset{offset.y},
      m_zOffset{offset.z},
      m_perlin{std::move(perlin)} {}

std::vector<float> Noise::generate() {
    int size = m_perlin->size();
    std::vector<float> map;

    if (m_scale <= 0.f) m_scale = 0.0001f;
    float maxPossibleHeight = 0.f;
    float amplitude = 1.f;

    for (int i = 0; i < m_octaves; ++i) {
        maxPossibleHeight += amplitude;
        amplitude *= m_persistence;
    }

    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            map.push_back(eval(glm::vec3{float(x), float(y), 0}));
        }
    }

    for (auto &h : map) {
        h = (h + 1.f) / (2.f * maxPossibleHeight / 2.f);
    }

    return map;
}

float Noise::eval(glm::vec3 p) {
    float amplitude = 1.f;
    float frequency = 1.f;
    float height = 0.f;

    for (int i = 0; i < m_octaves; ++i) {
        float sampleX = (float(p.x) + m_xOffset) / m_scale * frequency;
        float sampleY = (float(p.y) + m_yOffset) / m_scale * frequency;
        float sampleZ = (float(p.z) + m_zOffset) / m_scale * frequency;

        height += m_perlin->noise(sampleX, sampleY, sampleZ) * amplitude;

        amplitude *= m_persistence;
        frequency *= m_lacunarity;
    }

    return height;
}
}  // namespace daft::core