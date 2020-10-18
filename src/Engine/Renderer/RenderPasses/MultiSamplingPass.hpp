//
// Created by mathis on 05/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Rendering/FrameBufferObject.hpp>
#include <memory>

namespace daft::engine {
class MultiSamplingPass : public core::NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param width - width of the framebuffers.
     * @param height - height of the framebuffers.
     * @param numSample - number of samples in the input framebuffer.
     */
    MultiSamplingPass(int width, int height, int numSample, bool isHDR = false);

    /**
     * Default destructor.
     */
    ~MultiSamplingPass() = default;

    /**
     * Default move constructor.
     */
    MultiSamplingPass(MultiSamplingPass &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    MultiSamplingPass &operator=(MultiSamplingPass &&) noexcept = default;

    [[nodiscard]] const core::FrameBufferObject &resultFBO() const { return *m_fboOut; }

    /**
     * Get the texture to print on the screen
     * @return output color texture from the output fbo.
     */
    GLuint outTexture() { return m_fboOut->textures()[0]; }

    /**
     * Prepares to render to this pass.
     */
    void use() const { m_fboIn->use(); }

    /**
     * Finish rendering, gives the result to the output framebuffer.
     * @param width - width of the current opengl window.
     * @param height - height of the current opengl window.
     */
    void stop(int width, int height) const;

   private:
    std::unique_ptr<core::FrameBufferObject> m_fboIn{nullptr};
    std::unique_ptr<core::FrameBufferObject> m_fboOut{nullptr};
};
}  // namespace daft::engine