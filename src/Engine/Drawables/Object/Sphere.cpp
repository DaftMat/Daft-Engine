//
// Created by mathis on 08/08/2020.
//
#include "Sphere.hpp"

#include <Core/Utils/DrawableVisitor.hpp>
#include <array>

#define CONVHULL_3D_ENABLE
#include <ConvexHull3D/convhull_3d.h>

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
            case Type::Fibo:
                m_nrPoints = args[0];
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
        case Type::Fibo:
            createFiboSphere();
            break;
    }
}

void Sphere::createUVSphere() {
    core::AttribManager am;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> tangents;

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
            glm::vec3 t, b;
            core::orthoVectors(n, t, b);
            tangents.push_back(t);
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
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(am);
    m_meshObjects.emplace_back(std::move(meshes));
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
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> tangents;
    core::AttribManager am;

    // first vertex
    glm::vec3 fv{0.f, 1.f, 0.f};
    positions.push_back(fv * m_radius);
    normals.push_back(fv);
    glm::vec3 t, b;
    core::orthoVectors(fv, t, b);
    tangents.push_back(t);

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

        glm::vec3 t1, b1;
        core::orthoVectors(v1, t1, b1);
        tangents.push_back(t1);
        glm::vec3 t2, b2;
        core::orthoVectors(v2, t2, b2);
        tangents.push_back(t2);

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
    am.addAttrib(texCoords);
    am.addAttrib(tangents);

    m_meshObjects.clear();
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(am);
    m_meshObjects.emplace_back(std::move(meshes));
}

void Sphere::subdivideIcosahedron() {
    for (auto &obj : m_meshObjects) {
        std::vector<glm::vec3> tmpPositions = obj.meshes()[0].attribManager().getAttribs<glm::vec3>(0)->attribs;
        std::vector<glm::vec3> tmpNormals = obj.meshes()[0].attribManager().getAttribs<glm::vec3>(1)->attribs;
        std::vector<GLuint> tmpIndices = obj.meshes()[0].attribManager().indices();

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> tangents;
        glm::vec3 t, b;
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
            core::orthoVectors(tmpNormals[ind_v1], t, b);
            tangents.push_back(t);
            normals.push_back(new_n1);
            core::orthoVectors(new_n1, t, b);
            tangents.push_back(t);
            normals.push_back(new_n3);
            core::orthoVectors(new_n3, t, b);
            tangents.push_back(t);
            // 2nd triangle
            positions.push_back(new_p1);
            positions.push_back(tmpPositions[ind_v2]);
            positions.push_back(new_p2);

            normals.push_back(new_n1);
            core::orthoVectors(new_n1, t, b);
            tangents.push_back(t);
            normals.push_back(tmpNormals[ind_v2]);
            core::orthoVectors(tmpNormals[ind_v2], t, b);
            tangents.push_back(t);
            normals.push_back(new_n2);
            core::orthoVectors(new_n3, t, b);
            tangents.push_back(t);
            // 3rd triangle
            positions.push_back(new_p1);
            positions.push_back(new_p2);
            positions.push_back(new_p3);

            normals.push_back(new_n1);
            core::orthoVectors(new_n1, t, b);
            tangents.push_back(t);
            normals.push_back(new_n2);
            core::orthoVectors(new_n2, t, b);
            tangents.push_back(t);
            normals.push_back(new_n3);
            core::orthoVectors(new_n3, t, b);
            tangents.push_back(t);
            // 4th triangle
            positions.push_back(new_p3);
            positions.push_back(new_p2);
            positions.push_back(tmpPositions[ind_v3]);

            normals.push_back(new_n3);
            core::orthoVectors(new_n3, t, b);
            tangents.push_back(t);
            normals.push_back(new_n2);
            core::orthoVectors(new_n2, t, b);
            tangents.push_back(t);
            normals.push_back(tmpNormals[ind_v3]);
            core::orthoVectors(tmpPositions[ind_v3], t, b);
            tangents.push_back(t);

            /// 4 new triangles
            for (int j = 0; j < 12; ++j) am.indices().push_back(index + j);
            index += 12;
        }

        am.addAttrib(positions);
        am.addAttrib(normals);
        am.addAttrib(texCoords);
        am.addAttrib(tangents);

        obj.meshes()[0].reset(am);
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
                glm::vec3 pointOnUnitSphere = glm::normalize(pointOnUnitCube);

                positions.push_back(pointOnUnitSphere * m_radius);
                normals.push_back(pointOnUnitSphere);
                glm::vec3 t, b;
                core::orthoVectors(pointOnUnitSphere, t, b);
                tangents.push_back(t);
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
        am.addAttrib(tangents);
        meshes.emplace_back(core::Mesh(am));
    }

    m_meshObjects.clear();
    m_meshObjects.emplace_back(std::move(meshes));
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
        case Type::Fibo:
            sm.add("Points", m_nrPoints);
    }
    return sm;
}

void Sphere::setSettings(const core::SettingManager &s) {
    if (s.has("Type")) setType(Type(s.get<int>("Type")));
    if (m_update) return;
    if (s.has("Radius")) setRadius(s.get<float>("Radius"));
    switch (m_type) {
        case Type::UV:
            if (s.has("Meridians")) setMeridians(s.get<int>("Meridians"));
            if (s.has("Parallels")) setParallels(s.get<int>("Parallels"));
            break;
        case Type::Ico:
            if (s.has("Subdivisions")) setSubdivisions(s.get<int>("Subdivisions"));
            break;
        case Type::Cube:
            if (s.has("Resolution")) setResolution(s.get<int>("Resolution"));
            break;
        case Type::Fibo:
            if (s.has("Points")) setPoints(s.get<int>("Points"));
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

void Sphere::setPoints(int p) {
    if (p == m_nrPoints) return;
    m_nrPoints = p;
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

void Sphere::createFiboSphere() {
    core::AttribManager am;
    auto positions = fibo3D(m_nrPoints);
    auto normals = positions;
    std::vector<glm::vec2> texCoords;
    auto tangents = normals;
    am.indices() = triangulateFibo(positions);

    auto tempRadius = m_radius;
    std::for_each(positions.begin(), positions.end(), [tempRadius](glm::vec3 &pos) { pos *= tempRadius; });
    std::for_each(tangents.begin(), tangents.end(), [](glm::vec3 &tangent) {
        glm::vec3 t, b;
        core::orthoVectors(tangent, t, b);
        tangent = t;
    });

    am.addAttrib(positions);
    am.addAttrib(normals);

    m_meshObjects.clear();
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(am);
    m_meshObjects.emplace_back(std::move(meshes));
}

std::vector<glm::vec3> Sphere::fibo3D(int n) {
    float goldenAngle{glm::pi<float>() * (3.f - glm::sqrt(5.f))};
    std::vector<glm::vec3> points;
    float dz = 2.f / float(n);
    float z = 1.f - dz / 2.f;
    for (int i = 0; i < n; ++i) {
        float theta = float(i) * goldenAngle;
        float r = glm::sqrt(1.f - z * z);
        points.emplace_back(r * glm::cos(theta), z, r * glm::sin(theta));
        z -= dz;
    }
    return points;
}

std::vector<GLuint> Sphere::triangulateFibo(const std::vector<glm::vec3> &points) {
    std::vector<ch_vertex> passPoints;
    std::for_each(points.begin(), points.end(), [&passPoints](glm::vec3 p) {
        ch_vertex v;
        v.x = p.x;
        v.y = p.y;
        v.z = p.z;
        passPoints.push_back(v);
    });

    int *faceIndices = nullptr;
    int nFaces;

    convhull_3d_build(passPoints.data(), passPoints.size(), &faceIndices, &nFaces);

    std::vector<GLuint> indices;
    for (int i = 0; i < nFaces * 3; ++i) {
        indices.push_back(faceIndices[i]);
    }

    return indices;
}

}  // namespace daft::engine