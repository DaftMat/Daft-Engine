//
// Created by mathis on 16/10/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Rendering/ShaderProgram.hpp>
#include <Core/Utils/NonCopyable.hpp>

#include "MultiSamplingPass.hpp"

namespace daft::engine {
class HDRPass : public core::NonCopyable {
    HDRPass(int width, int height, int multisamples = 32);

    ~HDRPass() = default;

    HDRPass(HDRPass &&) noexcept = default;

    HDRPass &operator=(HDRPass &&) noexcept = default;

    GLuint outTexture() { return m_addFBO->textures()[0]; }

    void use() const { m_multisample->use(); }

    void stop(int width, int height);

   private:
    int m_width, m_height;

    std::unique_ptr<MultiSamplingPass> m_multisample{nullptr};  ///< to use to render the scene.
    std::unique_ptr<core::FrameBufferObject> m_bloomFBO{
        nullptr};  ///< to use to extract the bloom parts from the rendered scene.
    std::vector<std::unique_ptr<core::FrameBufferObject>> m_blurFBOs;  ///< to use to blur the extracted bloom parts.
    std::unique_ptr<core::FrameBufferObject> m_addFBO{
        nullptr};  ///< to use to add the bloom and hdr images into an std RGB image.

    std::unique_ptr<core::ShaderProgram> m_bloomShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_blurShader{nullptr};
    std::unique_ptr<core::ShaderProgram> m_addShader{nullptr};
};
}  // namespace daft::engine