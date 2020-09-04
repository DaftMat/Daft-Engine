//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <Engine/Drawables/Drawable.hpp>
#include <memory>
#include <utility>

#include "FrameBufferObject.hpp"
#include "ShaderProgram.hpp"

namespace daft::core {
/**
 * Base class for any one-pass renderer.
 */
class ENGINE_API PassRenderer : public NonCopyable {
   public:
    /**
     * Standard constructor.
     * @param fbo - fbo to render to.
     * @param shader - shader to use.
     */
    PassRenderer(std::shared_ptr<FrameBufferObject> fbo, std::shared_ptr<ShaderProgram> shader,
                 GLuint renderType = GL_TRIANGLES)
        : m_fbo{std::move(fbo)}, m_shader{std::move(shader)}, m_renderType{renderType} {}

    /**
     * Default destructor.
     */
    ~PassRenderer() = default;
    /**
     * Default move constructor.
     */
    PassRenderer(PassRenderer &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    PassRenderer &operator=(PassRenderer &&) noexcept = default;

    /**
     * Prepares the renderers to get drawables to draw.
     */
    void prepare();

    /**
     * Renders the passed drawable to the fbo.
     * @param d - drawable to draw.
     */
    virtual void render(engine::Drawable *d);

    /**
     * unbinds the renderer.
     */
    void unbind(int width, int height);

    /**
     * FBO getter.
     * @return the FrameBufferObject the renderer is rendering on.
     */
    auto &fbo() { return m_fbo; }

    /**
     * Shader getter.
     * @return the ShaderProgram used to render.
     */
    auto &shader() { return m_shader; }

   private:
    std::shared_ptr<FrameBufferObject> m_fbo;
    std::shared_ptr<ShaderProgram> m_shader;

    GLuint m_renderType;
};
}  // namespace daft::core