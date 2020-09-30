//
// Created by mathis on 12/08/2020.
//
#pragma once
#include <Engine/Drawables/Light/PointLight.hpp>
#include <Engine/Drawables/Object/BSpline.hpp>
#include <Engine/Drawables/Object/Cube.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <Engine/Drawables/Object/Sphere.hpp>
#include <Engine/Drawables/Object/Torus.hpp>

namespace daft::engine {
core::AttribManager createCircle(glm::vec3 pos = glm::vec3{0.f}, glm::vec3 normal = {0.f, 1.f, 0.f}, float radius = 1.f,
                                 int steps = 64);
core::AttribManager createStar(glm::vec3 pos = glm::vec3{0.f});
}  // namespace daft::engine