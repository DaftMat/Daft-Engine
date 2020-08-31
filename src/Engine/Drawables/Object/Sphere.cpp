//
// Created by mathis on 08/08/2020.
//
#include "Sphere.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {

int Sphere::m_nrSphere{0};

Sphere::Sphere(Sphere::Type type, const std::vector<int> &args, Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_type{type} {
    if (!args.empty()) {
        switch (m_type) {
            case Type::UV:
                m_meridians = args[0];
                m_parallels = args[1];
                break;
            case Type::Ico:
                m_subdivisions = args[0];
                break;
            case Type::Cube:
                m_resolution = args[0];
                break;
        }
    }
    Sphere::applyUpdate();
}

void Sphere::applyUpdate() {
    switch (m_type) {
        case Type::UV:
            createUVSphere();
            break;
        case Type::Ico:
            createIcoSphere();
            break;
        case Type::Cube:
            createCubeSphere();
            break;
    }
}

void Sphere::createUVSphere() {
    core::AttribManager am;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    /// geometry
    float mStep = (2.f * glm::pi<float>()) / float(m_meridians);
    float pStep = glm::pi<float>() / float(m_parallels);

    for (int i = 0; i <= m_parallels; ++i) {
        float pAngle = glm::pi<float>() / 2.f - float(i) * pStep;
        float xy = glm::cos(pAngle);
        float z = glm::sin(pAngle);

        for (int j = 0; j <= m_meridians; ++j) {
            float mAngle = float(j) * mStep;

            glm::vec3 pn{xy * glm::cos(mAngle), z, xy * glm::sin(mAngle)};
            positions.push_back(pn);
            texCoords.emplace_back(float(j) / float(m_meridians), float(i) / float(m_parallels));
        }
    }
    am.addAttrib(positions);
    am.addAttrib(positions);  ///< normals = positions
    am.addAttrib(texCoords);

    /// topology
    GLuint k1, k2;
    for (int i = 0; i < m_parallels; ++i) {
        k1 = i * (m_meridians + 1);
        k2 = k1 + m_meridians + 1;
        for (int j = 0; j < m_meridians; ++j, ++k1, ++k2) {
            if (i) {
                am.indices().push_back(k1 + 1);
                am.indices().push_back(k2);
                am.indices().push_back(k1);
            }
            if (i != (m_parallels - 1)) {
                am.indices().push_back(k2 + 1);
                am.indices().push_back(k2);
                am.indices().push_back(k1 + 1);
            }
        }
    }

    m_meshObjects.clear();
    m_meshObjects.emplace_back(core::Mesh(am));
}

void Sphere::createIcoSphere() {
    /// create the base icosahedron.
    createIcosahedron();
    for (int i = 0; i < m_subdivisions; ++i) subdivide(true);
}

void Sphere::createIcosahedron() {
    const float H_ANGLE = glm::pi<float>() / 180.f * 72.f;
    const float V_ANGLE = glm::atan(0.5f);

    float z, xy;
    float h_angle1 = -glm::pi<float>() / 2.f - H_ANGLE / 2.f;
    float h_angle2 = -glm::pi<float>() / 2.f;

    std::vector<glm::vec3> positions;
    core::AttribManager am;

    // first vertex
    positions.emplace_back(0.f, 1.f, 0.f);

    // 10 "middle" vertices
    for (int i = 1; i <= 5; ++i) {
        z = glm::sin(V_ANGLE);
        xy = glm::cos(V_ANGLE);

        glm::vec3 v1{xy * glm::cos(h_angle1), z, xy * glm::sin(h_angle1)};
        glm::vec3 v2{xy * glm::cos(h_angle2), -z, xy * glm::sin(h_angle2)};

        positions.push_back(v1);
        positions.push_back(v2);

        h_angle1 += H_ANGLE;
        h_angle2 += H_ANGLE;
    }

    // last vertex
    positions.emplace_back(0.f, -1.f, 0.f);

    // indices
    for (GLuint i = 1; i <= 9; i += 2) {
        // Top
        am.indices().push_back(0);
        am.indices().push_back(core::mod1(i + 2, 10));
        am.indices().push_back(i);
        // Middle up
        am.indices().push_back(i);
        am.indices().push_back(core::mod1(i + 2, 10));
        am.indices().push_back(core::mod1(i + 1, 10));
        // Middle down
        am.indices().push_back(core::mod1(i + 2, 10));
        am.indices().push_back(core::mod1(i + 3, 10));
        am.indices().push_back(core::mod1(i + 1, 10));
        // Bottom
        am.indices().push_back(core::mod1(i + 1, 10));
        am.indices().push_back(core::mod1(i + 3, 10));
        am.indices().push_back(11);
    }

    am.addAttrib(positions);
    am.addAttrib(positions);  ///< normals = positions;
    // am.addAttrib(texCoords);

    m_meshObjects.clear();
    m_meshObjects.emplace_back(core::Mesh(am));
}

void Sphere::createCubeSphere() {
    std::array<glm::vec3, 6> directions{
        glm::vec3(0.f, 0.f, 1.f),   // front
        glm::vec3(0.f, 0.f, -1.f),  // back
        glm::vec3(0.f, 1.f, 0.f),   // up
        glm::vec3(0.f, -1.f, 0.f),  // bottom
        glm::vec3(1.f, 0.f, 0.f),   // left
        glm::vec3(-1.f, 0.f, 0.f)   // right
    };

    m_meshObjects.clear();

    for (auto &dir : directions) {
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        core::AttribManager am;

        auto axisA = glm::vec3(dir.y, dir.z, dir.x);
        auto axisB = glm::cross(dir, axisA);
        for (int y = 0; y < m_resolution; ++y) {
            for (int x = 0; x < m_resolution; ++x) {
                int index = x + y * m_resolution;
                glm::vec2 percent = glm::vec2(x, y) / float(m_resolution - 1);
                glm::vec3 pointOnUnitCube = dir + (percent.x - 0.5f) * 2.f * axisA + (percent.y - 0.5f) * 2.f * axisB;
                glm::vec3 pointOnUnitSphere = glm::normalize(pointOnUnitCube);

                positions.push_back(pointOnUnitSphere);
                texCoords.push_back(percent);

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
        am.addAttrib(positions);  /// normals = positions
        am.addAttrib(texCoords);
        m_meshObjects.emplace_back(core::Mesh(am));
    }
}

void Sphere::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

}  // namespace daft::engine