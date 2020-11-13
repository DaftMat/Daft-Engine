//
// Created by mathis on 14/05/2020.
//
#pragma once

#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <vector>

namespace daft::core {
/**
 * Gives a function to get a smooth procedural height map.
 */
class ENGINE_API Perlin : public core::NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param seed - seed of the random variable.
     * @param size - size of the random array.
     */
    explicit Perlin(int seed = 2020, int size = 130);

    /**
     * Default destructor.
     */
    ~Perlin() = default;

    /**
     * Default move constructor.
     */
    Perlin(Perlin &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this
     */
    Perlin &operator=(Perlin &&) noexcept = default;

    /**
     * Evaluate the noise function given a 3D point p.
     * @param x - x coord of p.
     * @param y - y coord of p.
     * @param z - z coord of p.
     * @return noise value on point p.
     */
    [[nodiscard]] float noise(float x, float y, float z) const;

    /**
     * size of the random array.
     * @return size of the noise.
     */
    [[nodiscard]] int size() const { return p.size(); }

    /**
     * Seed setter.
     * @param seed - new seed.
     */
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