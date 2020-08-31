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
    for (int i = 0; i < m_subdivisions; ++i) subdivideIcoSphere();
    m_meshObjects.clear();
    m_meshObjects.emplace_back(core::Mesh(m_icoAm));
}

void Sphere::createIcosahedron() {
    const float H_ANGLE = glm::pi<float>() / 180.f * 72.f;
    const float V_ANGLE = glm::atan(0.5f);

    float z, xy;
    float h_angle1 = -glm::pi<float>() / 2.f - H_ANGLE / 2.f;
    float h_angle2 = -glm::pi<float>() / 2.f;

    // first vertex
    m_icoPositions.emplace_back(0.f, 1.f, 0.f);

    // 10 "middle" vertices
    for (int i = 1; i <= 5; ++i) {
        z = glm::sin(V_ANGLE);
        xy = glm::cos(V_ANGLE);

        glm::vec3 v1{xy * glm::cos(h_angle1), z, xy * glm::sin(h_angle1)};
        glm::vec3 v2{xy * glm::cos(h_angle2), -z, xy * glm::sin(h_angle2)};

        m_icoPositions.push_back(v1);
        m_icoPositions.push_back(v2);

        h_angle1 += H_ANGLE;
        h_angle2 += H_ANGLE;
    }

    // last vertex
    m_icoPositions.emplace_back(0.f, -1.f, 0.f);

    // indices
    for (GLuint i = 1; i <= 9; i += 2) {
        // Top
        m_icoAm.indices().push_back(0);
        m_icoAm.indices().push_back(core::mod1(i + 2, 10));
        m_icoAm.indices().push_back(i);
        // Middle up
        m_icoAm.indices().push_back(i);
        m_icoAm.indices().push_back(core::mod1(i + 2, 10));
        m_icoAm.indices().push_back(core::mod1(i + 1, 10));
        // Middle down
        m_icoAm.indices().push_back(core::mod1(i + 2, 10));
        m_icoAm.indices().push_back(core::mod1(i + 3, 10));
        m_icoAm.indices().push_back(core::mod1(i + 1, 10));
        // Bottom
        m_icoAm.indices().push_back(core::mod1(i + 1, 10));
        m_icoAm.indices().push_back(core::mod1(i + 3, 10));
        m_icoAm.indices().push_back(11);
    }

    m_icoAm.addAttrib(m_icoPositions);
    m_icoAm.addAttrib(m_icoPositions);  ///< normals = positions;
    // am.addAttrib(texCoords);
}

void Sphere::subdivideIcoSphere() {
    std::vector<glm::vec3> tmpPositions = m_icoPositions;
    std::vector<GLuint> tmpIndices = m_icoAm.indices();

    GLuint v1_ind, v2_ind, v3_ind, index = 0;
    glm::vec3 new_v1, new_v2, new_v3;

    m_icoPositions.clear();
    /// TODO: fix
    m_icoAm.clear();

    for (GLuint i = 0; i < tmpIndices.size(); i += 3) {
        v1_ind = tmpIndices[i];
        v2_ind = tmpIndices[i + 1];
        v3_ind = tmpIndices[i + 2];

        new_v1 = computeHalfVertex(tmpPositions[v1_ind], tmpPositions[v2_ind]);
        new_v2 = computeHalfVertex(tmpPositions[v2_ind], tmpPositions[v3_ind]);
        new_v3 = computeHalfVertex(tmpPositions[v1_ind], tmpPositions[v3_ind]);

        // 1st triangle
        m_icoPositions.push_back(tmpPositions[v1_ind]);
        m_icoPositions.push_back(new_v1);
        m_icoPositions.push_back(new_v3);
        // 2nd triangle
        m_icoPositions.push_back(new_v1);
        m_icoPositions.push_back(tmpPositions[v2_ind]);
        m_icoPositions.push_back(new_v2);
        // 3rd triangle
        m_icoPositions.push_back(new_v1);
        m_icoPositions.push_back(new_v2);
        m_icoPositions.push_back(new_v3);
        // 4th triangle
        m_icoPositions.push_back(new_v3);
        m_icoPositions.push_back(new_v2);
        m_icoPositions.push_back(tmpPositions[v3_ind]);

        /// 4 new triangles
        for (int j = 0; j < 12; ++j) {
            m_icoAm.indices().push_back(index + j);
        }
        index += 12;
    }

    m_icoAm.addAttrib(m_icoPositions);
    m_icoAm.addAttrib(m_icoPositions);  /// normals = positions
}

void Sphere::createCubeSphere() {}

void Sphere::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

}  // namespace daft::engine