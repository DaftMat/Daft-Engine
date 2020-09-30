//
// Created by daftmat on 30/09/2020.
//

#include "Adapters.hpp"

namespace daft::core {
void orthoVectors(glm::vec3 n, glm::vec3 &u, glm::vec3 &v) {
    n = glm::normalize(n);
    float sign = std::copysign(1.f, n[2]);
    const float a = -1.f / (sign + n[2]);
    const float b = n[0] * n[1] * a;
    u = glm::normalize(glm::vec3{1.f + sign + n[0] * n[0] * a, sign * b, -sign * n[0]});
    v = glm::normalize(glm::vec3{b, sign + n[1] * n[1] * a, -n[1]});
}
}  // namespace daft::core