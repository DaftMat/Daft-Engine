//
// Created by mathis on 16/10/2020.
//
#include "HDRPass.hpp"

namespace daft::engine {
HDRPass::HDRPass(int width, int height, int multisamples)
    : m_width{width},
      m_height{height},
      m_hdrQuad{-1.f, 1.f, 2.f, 2.f},
      m_blurQuad{-1.f, 1.f, 2.f, 2.f},
      m_addQuad{-1.f, 1.f, 2.f, 2.f},
      m_multisample{std::make_unique<MultiSamplingPass>(width, height, multisamples, true)},
      m_bloomFBO{std::make_unique<core::FrameBufferObject>(
          width, height, 1,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1}, true)},
      m_addFBO{std::make_unique<core::FrameBufferObject>(
          width, height, 1,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1}, true)},
      m_bloomShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/bloom.frag.glsl")},
      m_blurShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/blur.frag.glsl")},
      m_addShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/add.frag.glsl")} {
    m_blurFBOs.emplace_back(std::make_unique<core::FrameBufferObject>(
        width, height, 1, core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1},
        true));
    m_blurFBOs.emplace_back(std::make_unique<core::FrameBufferObject>(
        width, height, 1, core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1},
        true));

    m_bloomShader->use();
    m_bloomShader->setFloat("threshold", 1.f);
    m_bloomShader->stop();
    m_addShader->use();
    m_addShader->setBool("isHDR", true);
    m_addShader->stop();

    m_hdrQuad.setTexture(m_multisample->outTexture());
    m_blurQuad.setTexture(m_bloomFBO->textures()[0]);
    m_addQuad.setTexture(m_multisample->outTexture());
    m_addQuad.addTexture();
}

void HDRPass::stop(int width, int height) {
    m_multisample->stop(width, height);

    glDisable(GL_DEPTH_TEST);

    /// extract bloom parts
    m_bloomFBO->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_bloomShader->use();
    m_hdrQuad.prepare();
    m_hdrQuad.render(*m_bloomShader, GL_TRIANGLES);
    m_hdrQuad.unbind();
    m_bloomShader->stop();
    m_bloomFBO->stop(width, height);

    /// blur bloom parts
    bool horizontal = true, firstIt = true;
    int amout = 10;
    m_blurShader->use();
    for (int i = 0; i < amout; ++i) {
        m_blurFBOs[horizontal]->use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_blurShader->setBool("horizontal", horizontal);
        if (!firstIt)
            m_blurQuad.setTexture(m_blurFBOs[!horizontal]->textures()[0]);
        else
            m_blurQuad.setTexture(m_bloomFBO->textures()[0]);
        m_blurQuad.prepare();
        m_blurQuad.render(*m_blurShader, GL_TRIANGLES);
        m_blurQuad.unbind();
        m_blurFBOs[horizontal]->stop(width, height);
        horizontal = !horizontal;
        if (firstIt) firstIt = false;
    }
    m_addQuad.setTexture(m_blurFBOs[!horizontal]->textures()[0], 1);
    m_blurShader->stop();

    /// add the 2 images and apply tone mapping
    m_addFBO->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_addShader->use();
    m_addQuad.prepare();
    m_addQuad.render(*m_addShader, GL_TRIANGLES);
    m_addQuad.unbind();
    m_addShader->stop();
    m_addFBO->stop(width, height);

    glEnable(GL_DEPTH_TEST);
}
}  // namespace daft::engine
