//
// Created by mathis on 08/07/2020.
//
#include "Light.hpp"

namespace daft::engine {
int Light::m_nrLight{0};

void Light::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    if (selected())
        shader.setVec3("color", {1.f, 1.f, 0.f});
    else
        shader.setVec3("color", glm::vec3{1.f});
    m_mesh.prepare();
    m_mesh.render(GL_LINES);
    m_mesh.unbind();
    shader.setVec3("color", glm::vec3{0.f});
}

void Light::reset() {
    Drawable::reset();
    m_mesh.clear();
}

Light::Light(glm::vec3 color, Composite *parent, std::string name)
    : Drawable(parent, std::move(name)),
      m_shadowMap{"shadowMap", core::Texture::Type::NONE},
      m_fbo{std::make_unique<core::FrameBufferObject>(
          2048, 2048, 1,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::NONE, 0,
                                               core::FrameBufferObject::Attachments::Type::TEXTURE})},
      m_color{color} {}
}  // namespace daft::engine