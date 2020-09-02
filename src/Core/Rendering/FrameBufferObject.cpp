//
// Created by mathis on 02/09/2020.
//
#include "FrameBufferObject.hpp"

namespace daft::core {
void FrameBufferObject::initialize(daft::core::FrameBufferObject::Attachments a) {
    for (int i = 0; i < a.numColor; ++i) {
        if (a.color == Attachments::Type::TEXTURE) {
            addColorTexture();
        } else if (a.color == Attachments::Type::BUFFER) {
            addColorBuffer();
        }
    }
    if (a.depth == Attachments::Type::TEXTURE) {
        addDepthTexture();
    } else if (a.depth == Attachments::Type::BUFFER) {
        addDepthBuffer();
    }
    if (a.stencil == Attachments::Type::TEXTURE) {
        addStencilTexture();
    } else if (a.stencil == Attachments::Type::BUFFER) {
        addStencilBuffer();
    }
    if (a.stencil_depth == Attachments::Type::TEXTURE) {
        addDepthStencilTexture();
    } else if (a.stencil_depth == Attachments::Type::BUFFER) {
        addDepthStencilBuffer();
    }
    drawBuffers();
}
}  // namespace daft::core