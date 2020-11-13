//
// Created by mathis on 16/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Rendering/ShaderProgram.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <Engine/Renderer/Quad.hpp>

#include "MultiSamplingPass.hpp"

namespace daft::engine {
class HDRPass : public core::NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param width - width of the framebuffers.
     * @param height - height of the framebuffers.
     * @param multisamples - samples of the framebuffers.
     */
    HDRPass(int width, int height, int multisamples = 32);

    /**
     * Default destructor.
     */
    ~HDRPass() = default;

    /**
     * Default move constructor.
     */
    HDRPass(HDRPass &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    HDRPass &operator=(HDRPass &&) noexcept = default;

    /**
     * Resulting texture.
     * @return - texture of the scene.
     */
    GLuint outTexture() { return m_finalFBO->textures()[0]; }

    /**
     * Exposure getter.
     * @return exposure.
     */
    float exposure() const { return m_exposure; }

    /**
     * Exposure ref getter.
     * @return exposure.
     */
    float &exposure() { return m_exposure; }

    /**
     * Uses this pass.
     */
    void use() const { m_multisample->use(); }

    /**
     * Stops using this pass.
     * @param width - screen width.
     * @param height - screen height.
     */
    void stop(int width, int height);

   private:
    bool m_adaptive{false};
    float m_exposure{1.f};

    int m_width, m_height;
    Quad m_quad;

    std::unique_ptr<MultiSamplingPass> m_multisample{nullptr};
    std::vector<std::unique_ptr<core::FrameBufferObject>> m_pingpongFBOs;
    std::unique_ptr<core::FrameBufferObject> m_finalFBO{nullptr};

    std::unique_ptr<core::ShaderProgram> m_lumShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_meanShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_bloomShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_blurShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_addShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_finalShader{nullptr};
};
}  // namespace daft::engine