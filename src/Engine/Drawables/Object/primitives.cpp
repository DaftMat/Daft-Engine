//
// Created by daftmat on 30/09/2020.
//

#include "primitives.hpp"
namespace daft::engine {
core::AttribManager createCircle(glm::vec3 pos, glm::vec3 normal, float radius, int steps) {
    core::AttribManager am;
    std::vector<glm::vec3> positions;

    /// calculate orthogonal vectors
    glm::vec3 u{0.f}, v{0.f};
    core::orthoVectors(normal, u, v);

    /// draw circle
    float angle = 2 * glm::pi<float>() / float(steps);
    for (int i = 0; i <= steps; ++i) {
        float theta = float(i) * angle;
        positions.push_back(pos + radius * (u * glm::cos(theta) + v * glm::sin(theta)));
        if (i > 0) {
            am.indices().push_back(i - 1);
            am.indices().push_back(i);
        }
    }

    am.addAttrib(positions);
    return am;
}

core::AttribManager createStar(glm::vec3 pos) {
    std::vector<glm::vec3> dir{
        {0.f, 0.f, 1.f},   // front
        {0.f, 0.f, -1.f},  // back
        {0.f, 1.f, 0.f},   // top
        {0.f, -1.f, 0.f},  // bottom
        {1.f, 0.f, 0.f},   // right
        {-1.f, 0.f, 0.f}   // left
    };

    core::AttribManager am;
    std::vector<glm::vec3> positions;
    positions.emplace_back(0.f);

    for (size_t i = 0; i < dir.size(); ++i) {
        positions.push_back(dir[i] * 0.5f);
        am.indices().push_back(0);
        am.indices().push_back(i + 1);
    }

    am.addAttrib(positions);
    return am;
}
}  // namespace daft::engine