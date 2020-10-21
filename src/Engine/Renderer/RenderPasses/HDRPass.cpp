//
// Created by mathis on 16/10/2020.
//
#include "HDRPass.hpp"

namespace daft::engine {
HDRPass::HDRPass(int width, int height, int multisamples)
    : m_width{width},
      m_height{height},
      m_quad{-1.f, 1.f, 2.f, 2.f},
      m_multisample{std::make_unique<MultiSamplingPass>(width, height, multisamples, true)},
      m_finalFBO{std::make_unique<core::FrameBufferObject>(
          width, height, 1,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1}, true)},
      m_quadShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/quad.frag.glsl")},
      m_bloomShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/bloom.frag.glsl")},
      m_blurShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/blur.frag.glsl")},
      m_addShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/add.frag.glsl")},
      m_finalShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/hdr.frag.glsl")} {
    m_blurFBOs.emplace_back(std::make_unique<core::FrameBufferObject>(
        width, height, 1, core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1},
        true));
    m_blurFBOs.emplace_back(std::make_unique<core::FrameBufferObject>(
        width, height, 1, core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1},
        true));

    m_bloomShader->use();
    m_bloomShader->setFloat("threshold", 1.f);
    m_bloomShader->stop();

    m_quad.addTexture();
}

void HDRPass::stop(int width, int height) {
    m_multisample->stop(width, height);

    glDisable(GL_DEPTH_TEST);

    /// find luminance mean from hdr texture
    // if (m_adaptive) {
    //    m_quad.setTexture(m_multisample->outTexture());
    //    glm::vec2 texSize{m_width, m_height};
    //    bool change = false;
    //    m_quadShader->use();
    //    while (texSize.x > 1) {
    //        if (int(texSize.x) < m_width) m_quad.setTexture(m_blurFBOs[!change]->textures()[0]);
    //        texSize /= 2.f;
    //        if (texSize.x < 1.f) texSize.x = 1.f;
    //        if (texSize.y < 1.f) texSize.y = 1.f;
    //        m_blurFBOs[change]->setSize(texSize.x, texSize.y);
    //        m_blurFBOs[change]->use();
    //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //        m_quad.prepare();
    //        m_quad.render(*m_quadShader, GL_TRIANGLES);
    //        m_quad.unbind();
    //        change = !change;
    //    }
    //    float colorPixel[3];
    //    glReadPixels(0, 0, 1, 1, GL_RGB, GL_FLOAT, &colorPixel);
    //    float lumMean = 0.2126f * colorPixel[0] + 0.7152f * colorPixel[1] + 0.0722f * colorPixel[2];
    //    if (lumMean < glm::epsilon<float>()) lumMean = 0.01f;
    //    m_exposure = core::lerp(m_exposure, 0.3f / lumMean, 0.05);
    //    std::cout << m_exposure << std::endl;
    //    m_quadShader->stop();
    //    m_blurFBOs[!change]->stop(width, height);
    //    for (auto &fbo : m_blurFBOs) fbo->setSize(m_width, m_height);
    //}

    /// extract bloom parts
    m_quad.setTexture(m_multisample->outTexture());
    m_blurFBOs[0]->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_bloomShader->use();
    m_quad.prepare();
    m_quad.render(*m_bloomShader, GL_TRIANGLES);
    m_quad.unbind();
    m_bloomShader->stop();
    m_blurFBOs[0]->stop(width, height);

    /// blur bloom parts
    bool horizontal = true, firstIt = true;
    int amount = 16;
    m_blurShader->use();
    for (int i = 0; i < amount; ++i) {
        m_blurFBOs[horizontal]->use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_blurShader->setBool("horizontal", horizontal);
        m_quad.setTexture(m_blurFBOs[!horizontal]->textures()[0]);
        m_quad.prepare();
        m_quad.render(*m_blurShader, GL_TRIANGLES);
        m_quad.unbind();
        m_blurFBOs[horizontal]->stop(width, height);
        horizontal = !horizontal;
        if (firstIt) firstIt = false;
    }
    m_blurShader->stop();

    /// add the 2 images and apply tone mapping
    m_quad.setTexture(m_multisample->outTexture());
    m_quad.setTexture(m_blurFBOs[!horizontal]->textures()[0], 1);
    m_blurFBOs[horizontal]->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_addShader->use();
    m_quad.prepare();
    m_quad.render(*m_addShader, GL_TRIANGLES);
    m_quad.unbind();
    m_addShader->stop();
    m_blurFBOs[horizontal]->stop(width, height);

    m_quad.setTexture(m_blurFBOs[horizontal]->textures()[0]);
    m_finalFBO->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_finalShader->use();
    // m_finalShader->setFloat("exposure", m_exposure);
    m_quad.prepare();
    m_quad.render(*m_finalShader, GL_TRIANGLES);
    m_quad.unbind();
    m_finalShader->stop();
    m_finalFBO->stop(width, height);

    glEnable(GL_DEPTH_TEST);
}
}  // namespace daft::engine
