//
// Created by mathis on 08/08/2020.
//
#include "Sphere.hpp"

#include <Core/Utils/DrawableVisitor.hpp>
#include <array>

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
    std::vector<glm::vec3> normals;
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

            glm::vec3 n{xy * glm::cos(mAngle), z, xy * glm::sin(mAngle)};
            positions.push_back(n * m_radius);
            normals.push_back(n);
            texCoords.emplace_back(float(j) / float(m_meridians), float(i) / float(m_parallels));
        }
    }
    am.addAttrib(positions);
    am.addAttrib(normals);
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
    for (int i = 0; i < m_subdivisions; ++i) subdivideIcosahedron();
}

void Sphere::createIcosahedron() {
    const float H_ANGLE = glm::pi<float>() / 180.f * 72.f;
    const float V_ANGLE = glm::atan(0.5f);

    float h_angle1 = -glm::pi<float>() / 2.f - H_ANGLE / 2.f;
    float h_angle2 = -glm::pi<float>() / 2.f;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    core::AttribManager am;

    // first vertex
    glm::vec3 fv{0.f, 1.f, 0.f};
    positions.push_back(fv * m_radius);
    normals.push_back(fv);

    // 10 "middle" vertices
    for (int i = 1; i <= 5; ++i) {
        float z = glm::sin(V_ANGLE);
        float xy = glm::cos(V_ANGLE);

        glm::vec3 v1{xy * glm::cos(h_angle1), z, xy * glm::sin(h_angle1)};
        glm::vec3 v2{xy * glm::cos(h_angle2), -z, xy * glm::sin(h_angle2)};

        positions.push_back(v1 * m_radius);
        positions.push_back(v2 * m_radius);

        normals.push_back(v1);
        normals.push_back(v2);

        h_angle1 += H_ANGLE;
        h_angle2 += H_ANGLE;
    }

    // last vertex
    glm::vec3 lv{0.f, -1.f, 0.f};
    positions.push_back(lv * m_radius);
    normals.push_back(lv);

    // indices
    for (int i = 1; i <= 9; i += 2) {
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
    am.addAttrib(normals);
    // am.addAttrib(texCoords);

    m_meshObjects.clear();
    m_meshObjects.emplace_back(core::Mesh(am));
}

void Sphere::subdivideIcosahedron() {
    for (auto &obj : m_meshObjects) {
        std::vector<glm::vec3> tmpPositions = obj.mesh().attribManager().getAttribs<glm::vec3>(0)->attribs;
        std::vector<glm::vec3> tmpNormals = obj.mesh().attribManager().getAttribs<glm::vec3>(1)->attribs;
        std::vector<GLuint> tmpIndices = obj.mesh().attribManager().indices();

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        core::AttribManager am;
        GLuint ind_v1, ind_v2, ind_v3, index{0};
        glm::vec3 new_p1, new_n1, new_p2, new_n2, new_p3, new_n3;

        for (GLuint i = 0; i < tmpIndices.size(); i += 3) {
            ind_v1 = tmpIndices[i];
            ind_v2 = tmpIndices[i + 1];
            ind_v3 = tmpIndices[i + 2];

            new_n1 = computeHalfVertex(tmpNormals[ind_v1], tmpNormals[ind_v2]);
            new_n2 = computeHalfVertex(tmpNormals[ind_v2], tmpNormals[ind_v3]);
            new_n3 = computeHalfVertex(tmpNormals[ind_v1], tmpNormals[ind_v3]);

            new_p1 = m_radius * new_n1;
            new_p2 = m_radius * new_n2;
            new_p3 = m_radius * new_n3;

            // 1st triangle
            positions.push_back(tmpPositions[ind_v1]);
            positions.push_back(new_p1);
            positions.push_back(new_p3);

            normals.push_back(tmpNormals[ind_v1]);
            normals.push_back(new_n1);
            normals.push_back(new_n3);
            // 2nd triangle
            positions.push_back(new_p1);
            positions.push_back(tmpPositions[ind_v2]);
            positions.push_back(new_p2);

            normals.push_back(new_n1);
            normals.push_back(tmpNormals[ind_v2]);
            normals.push_back(new_n2);
            // 3rd triangle
            positions.push_back(new_p1);
            positions.push_back(new_p2);
            positions.push_back(new_p3);

            normals.push_back(new_n1);
            normals.push_back(new_n2);
            normals.push_back(new_n3);
            // 4th triangle
            positions.push_back(new_p3);
            positions.push_back(new_p2);
            positions.push_back(tmpPositions[ind_v3]);

            normals.push_back(new_n3);
            normals.push_back(new_n2);
            normals.push_back(tmpNormals[ind_v3]);

            /// 4 new triangles
            for (int j = 0; j < 12; ++j) am.indices().push_back(index + j);
            index += 12;
        }

        am.addAttrib(positions);
        am.addAttrib(normals);

        obj.mesh().reset(am);
    }
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
        std::vector<glm::vec3> normals;
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

                positions.push_back(pointOnUnitSphere * m_radius);
                normals.push_back(pointOnUnitSphere);
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
        am.addAttrib(normals);
        am.addAttrib(texCoords);
        m_meshObjects.emplace_back(core::Mesh(am));
    }
}

void Sphere::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

core::SettingManager Sphere::getSettings() const {
    core::SettingManager sm;
    sm.add("Type", core::toUType(m_type));
    sm.add("Radius", m_radius);
    switch (m_type) {
        case Type::UV:
            sm.add("Meridians", m_meridians);
            sm.add("Parallels", m_parallels);
            break;
        case Type::Ico:
            sm.add("Subdivisions", m_subdivisions);
            break;
        case Type::Cube:
            sm.add("Resolution", m_resolution);
            break;
    }
    return sm;
}

void Sphere::setSettings(const core::SettingManager &s) {
    setType(Type(s.get<int>("Type")));
    if (m_update) return;
    setRadius(s.get<float>("Radius"));
    switch (m_type) {
        case Type::UV:
            setMeridians(s.get<int>("Meridians"));
            setParallels(s.get<int>("Parallels"));
            break;
        case Type::Ico:
            setSubdivisions(s.get<int>("Subdivisions"));
            break;
        case Type::Cube:
            setResolution(s.get<int>("Resolution"));
            break;
    }
}

void Sphere::setMeridians(int m) {
    if (m == m_meridians) return;
    m_meridians = m;
    updateNextFrame();
}

void Sphere::setParallels(int p) {
    if (p == m_parallels) return;
    m_parallels = p;
    updateNextFrame();
}

void Sphere::setSubdivisions(int s) {
    if (s == m_subdivisions) return;
    m_subdivisions = s;
    updateNextFrame();
}

void Sphere::setResolution(int r) {
    if (r == m_resolution) return;
    m_resolution = r;
    updateNextFrame();
}

void Sphere::setType(Sphere::Type type) {
    if (type == m_type) return;
    m_type = type;
    updateNextFrame();
}

void Sphere::setRadius(float r) {
    if (r == m_radius) return;
    m_radius = r;
    updateNextFrame();
}

}  // namespace daft::engine