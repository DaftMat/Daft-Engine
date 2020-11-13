//
// Created by daftmat on 23/09/2020.
//

#include "Cube.hpp"

#include <array>

namespace daft::engine {
int Cube::m_nrCube{0};

Cube::Cube(float radius, int resolution, daft::engine::Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_radius{radius}, m_resolution{resolution} {
    createCube();
}

core::SettingManager Cube::getSettings() const {
    core::SettingManager s{};
    s.add("Radius", m_radius);
    s.add("Resolution", m_resolution);
    return s;
}

void Cube::setSettings(const core::SettingManager &s) {
    if (s.has("Radius")) setRadius(s.get<float>("Radius"));
    if (s.has("Resolution")) setResolution(s.get<int>("Resolution"));
}

void Cube::setRadius(float r) {
    if (m_radius == r) return;
    m_radius = r;
    updateNextFrame();
}

void Cube::setResolution(int r) {
    if (m_resolution == r) return;
    m_resolution = r;
    updateNextFrame();
}

void Cube::applyUpdate() { createCube(); }

void Cube::createCube() {
    std::array<glm::vec3, 6> directions{
        glm::vec3(0.f, 0.f, 1.f),   // front
        glm::vec3(0.f, 0.f, -1.f),  // back
        glm::vec3(0.f, 1.f, 0.f),   // up
        glm::vec3(0.f, -1.f, 0.f),  // bottom
        glm::vec3(1.f, 0.f, 0.f),   // left
        glm::vec3(-1.f, 0.f, 0.f)   // right
    };

    std::vector<core::Mesh> meshes;

    for (auto &dir : directions) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> tangents;
        core::AttribManager am;

        auto axisA = glm::vec3(dir.y, dir.z, dir.x);
        auto axisB = glm::cross(dir, axisA);
        for (int y = 0; y < m_resolution; ++y) {
            for (int x = 0; x < m_resolution; ++x) {
                int index = x + y * m_resolution;
                glm::vec2 percent = glm::vec2(x, y) / float(m_resolution - 1);
                glm::vec3 pointOnUnitCube = dir + (percent.x - 0.5f) * 2.f * axisA + (percent.y - 0.5f) * 2.f * axisB;

                positions.push_back(pointOnUnitCube * m_radius);
                normals.push_back(dir);
                texCoords.push_back(percent);
                glm::vec3 t, b;
                core::orthoVectors(dir, t, b);
                tangents.push_back(t);

                /// Triangles
                if (x != m_resolution - 1 && y != m_resolution - 1) {
                    am.indices().push_back(index);
                    am.indices().push_back(index + m_resolution + 1);
                    am.indices().push_back(index + m_resolution);

                    am.indices().push_back(index);
                    am.indices().push_back(index + 1);
                    am.indices().push_back(index + m_resolution + 1);
                }
            }
        }

        am.addAttrib(positions);
        am.addAttrib(normals);
        am.addAttrib(texCoords);
        meshes.emplace_back(core::Mesh{am});
    }

    m_meshObjects.clear();
    m_meshObjects.emplace_back(std::move(meshes));
}
}  // namespace daft::engine
