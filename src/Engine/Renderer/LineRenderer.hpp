//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Rendering/PassRenderer.hpp>

namespace daft::engine {
/**
 * A renderer to render lines.
 */
class ENGINE_API LineRenderer : public core::PassRenderer {
   public:
    /**
     * Standard constructor.
     * @param fbo - fbo to render to.
     * @param shader - shader to be used.
     */
    LineRenderer(std::shared_ptr<core::FrameBufferObject> fbo, std::shared_ptr<core::ShaderProgram> shader)
        : core::PassRenderer{std::move(fbo), std::move(shader), GL_LINES} {}

    /**
     * Renders a Drawable to the fbo.
     * @param d - drawable to render.
     */
    void render(engine::Drawable *d) override;
};
}  // namespace daft::engine