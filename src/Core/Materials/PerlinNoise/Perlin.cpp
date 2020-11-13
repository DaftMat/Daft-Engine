//
// Created by mathis on 15/05/2020.
//

#include "Perlin.hpp"

#include <Core/Random.hpp>

namespace daft::core {
Perlin::Perlin(int seed, int size) { init(seed, size); }

float Perlin::noise(float x, float y, float z) const {
    int X = (int)glm::floor(x) & 127;
    int Y = (int)glm::floor(y) & 127;
    int Z = (int)glm::floor(z) & 127;
    x -= glm::floor(x);
    y -= glm::floor(y);
    z -= glm::floor(z);
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);
    const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    const int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    float res = lerp(w,
                     lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
                          lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
                     lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
                          lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
    return res;
}

float Perlin::grad(int hash, float x, float y, float z) {
    int h = hash & 15;
    float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void Perlin::init(int seed, int size) {
    if (size < 129) size = 129;
    m_size = size;
    Random::seed(seed);
    p.clear();
    for (int i = 0; i < size; ++i) p.push_back((int)Random::get(0, 127));
}
}  // namespace daft::core