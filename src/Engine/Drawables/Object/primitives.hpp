//
// Created by mathis on 12/08/2020.
//
#pragma once
#include <Core/Geometry/AttribManager.hpp>

namespace daft::engine {
core::AttribManager createCircle(glm::vec3 pos = glm::vec3{0.f}, glm::vec3 normal = {0.f, 1.f, 0.f}, float radius = 1.f,
                                 int steps = 64);
core::AttribManager createStar(glm::vec3 pos = glm::vec3{0.f});
}  // namespace daft::engine