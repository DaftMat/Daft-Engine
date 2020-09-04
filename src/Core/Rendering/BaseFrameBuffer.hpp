//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/Logger.hpp>
#include <Core/Utils/NonCopyable.hpp>

namespace daft::core {
/**
 * Base class for a Framebuffer object.
 */
class ENGINE_API BaseFrameBuffer : public core::NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param width - width of the framebuffer.
     * @param height - height of the framebuffer.
     * @param numSamples - number of samples per pixel.
     */
    BaseFrameBuffer(int width, int height, int numSamples)
        : m_width{width}, m_height{height}, m_numSamples{numSamples}, m_isValid{true} {
        glGenFramebuffers(1, &m_fbo);
        std::stringstream ss;
        ss << "FrameBuffer created. ID: " << m_fbo;
        Logger::info(std::move(ss));
    }

    /**
     * Destructor.
     */
    ~BaseFrameBuffer();

    /**
     * Move constructor.
     */
    BaseFrameBuffer(BaseFrameBuffer &&) noexcept;

    /**
     * Move assignment operator.
     * @return ref to this.
     */
    BaseFrameBuffer &operator=(BaseFrameBuffer &&) noexcept;

    /**
     * Activates the framebuffer.
     * The next frames will be rendered on this framebuffer.
     */
    void use() const;

    /**
     * Stops using this framebuffer.
     * The next frames will be rendered on the screen's framebuffer.
     */
    void stop(int width, int height) const;

    /** Resolves one fbo's color buffer to the screen's fbo.
     *
     * @param width - screen width.
     * @param height - screen height.
     * @param index - index of the color buffer to resolve.
     */
    void resolve(int width, int height, int index = 0) const;

    /** Resolves one fbo's color buffer to another fbo.
     *
     * @param frameBuffer - other fbo.
     * @param index - index of the color buffer to resolve.
     */
    void resolve(BaseFrameBuffer &fb, int index = 0) const;

    /**
     * Textures getter.
     * @return list of the framebuffer's textures.
     */
    [[nodiscard]] const std::vector<GLuint> &textures() const { return m_textures; }

    /**
     * Buffers getter.
     * @return list of the framebuffer's buffers.
     */
    [[nodiscard]] const std::vector<GLuint> &buffers() const { return m_buffers; }

    /**
     * Default fbo setter.
     * Because Qt didn't want to be simple.
     * @param fbo - default (screen) framebuffer object.
     */
    static void setDefaultFbo(GLuint fbo) { m_defaultFbo = fbo; }

   protected:
    void addColorBuffer();
    void addDepthBuffer();
    void addStencilBuffer();
    void addDepthStencilBuffer();
    void addColorTexture();
    void addDepthTexture();
    void addStencilTexture();
    void addDepthStencilTexture();

    void drawBuffers() const;

   private:
    static GLuint m_defaultFbo;

    int m_width, m_height;
    GLuint m_fbo{0};
    std::vector<GLuint> m_textures;
    std::vector<GLuint> m_buffers;

    int m_numSamples;

    bool m_stencil{false}, m_depth{false}, m_stencil_depth{false};
    int m_num_color{0};

    bool m_isValid{false};
};
}  // namespace daft::core