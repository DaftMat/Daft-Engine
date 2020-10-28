//
// Created by mathis on 14/05/2020.
//
#pragma once

#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <vector>

namespace daft::core {
class ENGINE_API Perlin : public core::NonCopyable {
   public:
    explicit Perlin(int seed = 2020, int size = 255);

    ~Perlin() = default;

    Perlin(Perlin &&) noexcept = default;

    Perlin &operator=(Perlin &&) noexcept = default;

    [[nodiscard]] float noise(float x, float y, float z) const;

    [[nodiscard]] int size() const { return p.size(); }

    void setSeed(int seed) { init(seed, m_size); }

   private:
    void init(int seed, int size);

    static constexpr float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

    static constexpr float lerp(float t, float a, float b) { return a + t * (b - a); }

    static float grad(int hash, float x, float y, float z);

    std::vector<int> p;
    int m_size;
};
}  // namespace daft::core