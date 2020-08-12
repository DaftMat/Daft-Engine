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
    Sphere::update();
}

void Sphere::update() {
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
    /// sectors = meridians
    /// stacks = parallels
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

            glm::vec3 pn{xy * glm::cos(mAngle), z, xy * glm::sin(mAngle)};
            positions.push_back(pn);
            normals.push_back(pn);
            texCoords.emplace_back(float(j) / float(m_meridians), float(i) / float(m_parallels));
        }
    }

    /// topology
    GLuint k1, k2;
    for (int i = 0; i < m_parallels; ++i) {
        k1 = i * (m_meridians + 1);
        k2 = k1 + m_meridians + 1;
        for (int j = 0; j < m_meridians; ++j) {
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

void Sphere::createIcoSphere() {}

void Sphere::createCubeSphere() {}

void Sphere::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

}  // namespace daft::engine