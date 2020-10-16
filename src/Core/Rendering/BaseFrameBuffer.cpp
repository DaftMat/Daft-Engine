//
// Created by mathis on 02/09/2020.
//
#include "BaseFrameBuffer.hpp"

#include <Core/Utils/Logger.hpp>

namespace daft::core {
GLuint BaseFrameBuffer::m_defaultFbo{0};

BaseFrameBuffer::~BaseFrameBuffer() {
    if (!m_isValid) return;
    for (GLuint &b : m_buffers) {
        glDeleteBuffers(1, &b);
    }
    for (GLuint &t : m_textures) {
        glDeleteTextures(1, &t);
    }
    std::stringstream ss;
    ss << "FrameBuffer of ID: " << m_fbo << " deleted";
    Logger::info(std::move(ss));
    glDeleteFramebuffers(1, &m_fbo);
}

BaseFrameBuffer::BaseFrameBuffer(BaseFrameBuffer &&o) noexcept
    : m_width{o.m_width},
      m_height{o.m_height},
      m_fbo{o.m_fbo},
      m_textures{std::move_if_noexcept(o.m_textures)},
      m_buffers{std::move_if_noexcept(o.m_buffers)},
      m_numSamples{o.m_numSamples},
      m_stencil{o.m_stencil},
      m_depth{o.m_depth},
      m_stencil_depth{o.m_stencil_depth},
      m_num_color{o.m_num_color},
      m_isValid{true} {
    o.m_isValid = false;
}

BaseFrameBuffer &BaseFrameBuffer::operator=(BaseFrameBuffer &&o) noexcept {
    m_width = o.m_width;
    m_height = o.m_height;
    m_fbo = o.m_fbo;
    m_textures = std::move_if_noexcept(o.m_textures);
    m_buffers = std::move_if_noexcept(o.m_buffers);
    m_numSamples = o.m_numSamples;
    m_stencil = o.m_stencil;
    m_depth = o.m_depth;
    m_stencil_depth = o.m_stencil_depth;
    m_num_color = o.m_num_color;
    m_isValid = o.m_isValid;
    o.m_isValid = false;
    return *this;
}

void BaseFrameBuffer::use() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
        std::stringstream ss;
        ss << "Framebuffer is not complete.";
        core::Logger::error(std::move(ss));
        return;
    }
    glViewport(0, 0, m_width, m_height);
}

void BaseFrameBuffer::stop(int width, int height) const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    glViewport(0, 0, width, height);
}

void BaseFrameBuffer::resolve(int width, int height, int index) const {
    if (index < 0) index = 0;
    if (index > m_num_color - 1) index = m_num_color - 1;
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_defaultFbo);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glDrawBuffer(GL_BACK);
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
}

void BaseFrameBuffer::resolve(BaseFrameBuffer &fb, int index) const {
    if (index < 0) index = 0;
    if (index > m_num_color - 1) index = m_num_color - 1;
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fb.m_fbo);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
    glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, fb.m_width, fb.m_height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
}

void BaseFrameBuffer::addColorBuffer() {
    if (m_num_color > GL_COLOR_ATTACHMENT31) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    GLuint format = m_isHDR ? GL_RGB16F : GL_RGB;
    if (m_numSamples == 1)
        glRenderbufferStorage(GL_RENDERBUFFER, format, m_width, m_height);
    else
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, format, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_num_color++, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_buffers.push_back(rbo);
}

void BaseFrameBuffer::addDepthBuffer() {
    if (m_depth) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if (m_numSamples == 1)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_width, m_height);
    else
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_DEPTH_COMPONENT, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_depth = true;
    m_buffers.push_back(rbo);
}

void BaseFrameBuffer::addStencilBuffer() {
    if (m_stencil) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if (m_numSamples == 1)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX, m_width, m_height);
    else
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_STENCIL_INDEX, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_stencil = true;
    m_buffers.push_back(rbo);
}

void BaseFrameBuffer::addDepthStencilBuffer() {
    if (m_stencil_depth) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    if (m_numSamples == 1)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
    else
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_numSamples, GL_DEPTH24_STENCIL8, m_width, m_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_stencil_depth = true;
    m_buffers.push_back(rbo);
}

void BaseFrameBuffer::addColorTexture() {
    if (m_num_color > GL_COLOR_ATTACHMENT31) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    GLuint format = m_isHDR ? GL_RGB16F : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_num_color++, GL_TEXTURE_2D, tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_textures.push_back(tex);
}

void BaseFrameBuffer::addDepthTexture() {
    if (m_depth) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_depth = true;
    m_textures.push_back(tex);
}

void BaseFrameBuffer::addStencilTexture() {
    if (m_stencil) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX16, m_width, m_height, 0, GL_STENCIL_INDEX, GL_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_stencil = true;
    m_textures.push_back(tex);
}

void BaseFrameBuffer::addDepthStencilTexture() {
    if (m_stencil_depth) return;
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_width, m_height, 0, GL_DEPTH24_STENCIL8, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tex, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
    m_stencil_depth = true;
    m_textures.push_back(tex);
}

void BaseFrameBuffer::drawBuffers() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    auto *bufs = new GLuint[m_num_color];
    for (int i = 0; i < m_num_color; ++i) bufs[i] = GL_COLOR_ATTACHMENT0 + i;
    glDrawBuffers(m_num_color, bufs);
    delete[] bufs;
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFbo);
}
}  // namespace daft::core