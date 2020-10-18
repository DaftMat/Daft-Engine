//
// Created by mathis on 16/10/2020.
//
#include "HDRPass.hpp"

namespace daft::engine {
HDRPass::HDRPass(int width, int height, int multisamples)
    : m_width{width},
      m_height{height},
      m_hdrQuad{-1.f, 1.f, 2.f, 2.f},
      m_multisample{std::make_unique<MultiSamplingPass>(width, height, multisamples, true)},
      m_bloomFBO{std::make_unique<core::FrameBufferObject>(
          width, height, multisamples,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1}, true)},
      m_addFBO{std::make_unique<core::FrameBufferObject>(
          width, height, multisamples,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1}, true)},
      m_bloomShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/hdr.frag.glsl")},
      m_blurShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/blur.frag.glsl")},
      m_addShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/add.frag.glsl")} {
    m_hdrQuad.setTexture(m_multisample->outTexture());
}

void HDRPass::stop(int width, int height) {
    m_multisample->stop(width, height);

    m_addFBO->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    m_bloomShader->use();
    m_hdrQuad.render(*m_bloomShader);
    m_bloomShader->stop();
    m_addFBO->stop(width, height);
}
}  // namespace daft::engine
