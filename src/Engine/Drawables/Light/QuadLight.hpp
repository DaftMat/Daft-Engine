//
// Created by mathis on 28/11/2020.
//
#pragma once
#include <API.hpp>

#include "Light.hpp"

namespace daft::engine {
class ENGINE_API QuadLight : public Light {
    /**
     * Default/standard constructor.
     * @param mesh - line mesh that represents the light.
     * @param color - color emitted by the light.
     */
    explicit QuadLight(glm::vec3 color = glm::vec3{1.f}, Composite *parent = nullptr,
                       std::string name = "QuadLight" + std::to_string(m_nrQuadLight++))
        : Light{color, parent, std::move(name)} {}

    /**
     * Destructor.
     */
    ~QuadLight() override { Light::reset(); }

    /**
     * Default move constructor.
     */
    QuadLight(QuadLight &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    QuadLight &operator=(QuadLight &&) noexcept = default;

   private:
    static int m_nrQuadLight;
};
}  // namespace daft::engine