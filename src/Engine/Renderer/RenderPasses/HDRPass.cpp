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
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1})},
      m_lumShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/lum.frag.glsl")},
      m_meanShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/mean.frag.glsl")},
      m_bloomShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/bloom.frag.glsl")},
      m_blurShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/blur.frag.glsl")},
      m_addShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/add.frag.glsl")},
      m_finalShader{std::make_unique<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/hdr.frag.glsl")} {
    m_pingpongFBOs.emplace_back(std::make_unique<core::FrameBufferObject>(
        width, height, 1, core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1},
        true));
    m_pingpongFBOs.emplace_back(std::make_unique<core::FrameBufferObject>(
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
    if (m_adaptive) {
        /// calculate luminance
        m_quad.setTexture(m_multisample->outTexture());
        m_pingpongFBOs[0]->use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_lumShader->use();
        m_quad.prepare();
        m_quad.render(*m_lumShader, GL_TRIANGLES);
        m_quad.unbind();
        m_lumShader->stop();
        m_pingpongFBOs[0]->stop(width, height);

        /// calculate mean
        glm::vec2 texSize{m_width, m_height};
        bool change = true;
        m_meanShader->use();
        while (texSize.x > 1) {
            m_quad.setTexture(m_pingpongFBOs[!change]->textures()[0]);
            texSize /= 2.f;
            if (texSize.x < 1.f) texSize.x = 1.f;
            if (texSize.y < 1.f) texSize.y = 1.f;
            m_pingpongFBOs[change]->use();
            m_pingpongFBOs[change]->setSize(texSize.x, texSize.y);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            m_quad.prepare();
            m_quad.render(*m_meanShader, GL_TRIANGLES);
            m_quad.unbind();
            change = !change;
        }
        float colorPixel[3];
        glReadPixels(0, 0, 1, 1, GL_RGB, GL_FLOAT, &colorPixel);
        float lumMean = colorPixel[0] / float(m_width * m_height);
        std::cout << lumMean << std::endl;
        if (lumMean < 0.1f) lumMean = 0.1f;
        m_exposure = core::lerp(0.5f / lumMean, m_exposure, 0.05);
        m_meanShader->stop();
        m_pingpongFBOs[0]->stop(width, height);
        m_pingpongFBOs[1]->stop(width, height);
        m_pingpongFBOs[0]->setSize(m_width, m_height);
        m_pingpongFBOs[1]->setSize(m_width, m_height);
    }

    /// extract bloom parts
    m_quad.setTexture(m_multisample->outTexture());
    m_pingpongFBOs[0]->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_bloomShader->use();
    m_quad.prepare();
    m_quad.render(*m_bloomShader, GL_TRIANGLES);
    m_quad.unbind();
    m_bloomShader->stop();
    m_pingpongFBOs[0]->stop(width, height);

    /// blur bloom parts
    bool horizontal = true;
    int amount = 10;
    m_blurShader->use();
    for (int i = 0; i < amount; ++i) {
        m_pingpongFBOs[horizontal]->use();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_blurShader->setBool("horizontal", horizontal);
        m_quad.setTexture(m_pingpongFBOs[!horizontal]->textures()[0]);
        m_quad.prepare();
        m_quad.render(*m_blurShader, GL_TRIANGLES);
        m_quad.unbind();
        m_pingpongFBOs[horizontal]->stop(width, height);
        horizontal = !horizontal;
    }
    m_blurShader->stop();

    /// add the 2 images and apply tone mapping
    m_quad.setTexture(m_multisample->outTexture());
    m_quad.setTexture(m_pingpongFBOs[!horizontal]->textures()[0], 1);
    m_pingpongFBOs[horizontal]->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_addShader->use();
    m_quad.prepare();
    m_quad.render(*m_addShader, GL_TRIANGLES);
    m_quad.unbind();
    m_addShader->stop();
    m_pingpongFBOs[horizontal]->stop(width, height);

    m_quad.setTexture(m_pingpongFBOs[horizontal]->textures()[0]);
    m_finalFBO->use();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_finalShader->use();
    m_finalShader->setFloat("exposure", m_exposure);
    m_quad.prepare();
    m_quad.render(*m_finalShader, GL_TRIANGLES);
    m_quad.unbind();
    m_finalShader->stop();
    m_finalFBO->stop(width, height);

    glEnable(GL_DEPTH_TEST);
}
}  // namespace daft::engine
