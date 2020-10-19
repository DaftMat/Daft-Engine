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
    HDRPass(int width, int height, int multisamples = 32);

    ~HDRPass() = default;

    HDRPass(HDRPass &&) noexcept = default;

    HDRPass &operator=(HDRPass &&) noexcept = default;

    GLuint outTexture() { return m_addFBO->textures()[0]; }

    void use() const { m_multisample->use(); }

    void stop(int width, int height);

   private:
    int m_width, m_height;
    Quad m_hdrQuad;
    Quad m_blurQuad;
    Quad m_addQuad;

    std::unique_ptr<MultiSamplingPass> m_multisample{nullptr};
    std::unique_ptr<core::FrameBufferObject> m_bloomFBO{nullptr};
    std::vector<std::unique_ptr<core::FrameBufferObject>> m_blurFBOs;
    std::unique_ptr<core::FrameBufferObject> m_addFBO{nullptr};

    std::unique_ptr<core::ShaderProgram> m_bloomShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_blurShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_addShader{nullptr};
};
}  // namespace daft::engine