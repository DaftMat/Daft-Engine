//
// Created by mathis on 02/09/2020.
//
#include "Quad.hpp"

#include <Core/Materials/Material.hpp>
#include <Core/Materials/Texture.hpp>

namespace daft::engine {
Quad::Quad(float x, float y, float width, float height) {
    core::AttribManager am;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;

    am.indices() = {0, 1, 2, 0, 2, 3};

    positions.emplace_back(x, y, 0.f);
    texCoords.emplace_back(0.f, 1.f);

    positions.emplace_back(x + width, y, 0.f);
    texCoords.emplace_back(1.f, 1.f);

    positions.emplace_back(x + width, y - height, 0.f);
    texCoords.emplace_back(1.f, 0.f);

    positions.emplace_back(x, y - height, 0.f);
    texCoords.emplace_back(0.f, 0.f);

    am.addAttrib(positions);
    am.addAttrib(texCoords);

    m_mesh = core::Mesh(am);
    m_material = std::make_shared<core::Material>();
    addTexture();
}

void Quad::addTexture() {
    m_material->addTexture(
        core::Texture("quadTexture[" + std::to_string(m_material->textures().size()) + "]", core::Texture::Type::NONE));
}

void Quad::setTexture(int id, int i) { m_material->textures()[i].id() = id; }

void Quad::prepare() const {
    m_mesh.prepare();
    m_material->prepare();
}

void Quad::render(const core::ShaderProgram &shader, GLuint mode) const {
    m_material->loadToShader(shader, "");
    m_mesh.render(mode);
}
}  // namespace daft::engine