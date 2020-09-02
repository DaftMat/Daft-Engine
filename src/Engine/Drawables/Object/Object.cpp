//
// Created by mathis on 08/07/2020.
//
#include "Object.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {

int Object::m_nrObject{0};

Object::Object(Composite *parent, std::string name, std::vector<MeshObject> mos) noexcept
    : Drawable(parent, std::move_if_noexcept(name)), m_meshObjects{std::move_if_noexcept(mos)} {}

Object::Object(Composite *parent, MeshObject mo) noexcept : Drawable(parent), m_meshObjects{} {
    m_meshObjects.emplace_back(std::move_if_noexcept(mo));
}

Object::~Object() noexcept { Object::reset(); }

void Object::render(const core::ShaderProgram &shader, GLuint type) {
    shader.setMat4("model", model());
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        mo.render(type);
        mo.unbind();
    }
}

void Object::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Object::reset() {
    Drawable::reset();
    m_meshObjects.clear();
}

void Object::update() {
    if (m_update) {
        applyUpdate();
        m_update = false;
    }
}

void Object::subdivide(bool normalsArePositions) {
    /// naive subdivision algorithm for now
    /// in the future : half-edges
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

            new_p1 = computeHalfVertex(tmpPositions[ind_v1], tmpPositions[ind_v2]);
            new_p2 = computeHalfVertex(tmpPositions[ind_v2], tmpPositions[ind_v3]);
            new_p3 = computeHalfVertex(tmpPositions[ind_v1], tmpPositions[ind_v3]);

            if (!normalsArePositions) {
                new_n1 = computeHalfVertex(tmpNormals[ind_v1], tmpNormals[ind_v2]);
                new_n2 = computeHalfVertex(tmpNormals[ind_v2], tmpNormals[ind_v3]);
                new_n3 = computeHalfVertex(tmpNormals[ind_v1], tmpNormals[ind_v3]);
            }

            // 1st triangle
            positions.push_back(tmpPositions[ind_v1]);
            positions.push_back(new_p1);
            positions.push_back(new_p3);
            // 2nd triangle
            positions.push_back(new_p1);
            positions.push_back(tmpPositions[ind_v2]);
            positions.push_back(new_p2);
            // 3rd triangle
            positions.push_back(new_p1);
            positions.push_back(new_p2);
            positions.push_back(new_p3);
            // 4th triangle
            positions.push_back(new_p3);
            positions.push_back(new_p2);
            positions.push_back(tmpPositions[ind_v3]);

            if (!normalsArePositions) {
                // 1st triangle
                normals.push_back(tmpNormals[ind_v1]);
                normals.push_back(new_n1);
                normals.push_back(new_n3);
                // 2nd triangle
                normals.push_back(new_n1);
                normals.push_back(tmpNormals[ind_v2]);
                normals.push_back(new_n2);
                // 3rd triangle
                normals.push_back(new_n1);
                normals.push_back(new_n2);
                normals.push_back(new_n3);
                // 4th triangle
                normals.push_back(new_n3);
                normals.push_back(new_n2);
                normals.push_back(tmpNormals[ind_v3]);
            }

            /// 4 new triangles
            for (int j = 0; j < 12; ++j) am.indices().push_back(index + j);
            index += 12;
        }

        am.addAttrib(positions);
        if (!normalsArePositions) {
            am.addAttrib(normals);
        } else {
            am.addAttrib(positions);
        }

        obj.mesh().reset(am);
    }
}

}  // namespace daft::engine