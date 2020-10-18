//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>

#include "BaseFrameBuffer.hpp"

namespace daft::core {
class FrameBufferObject : public BaseFrameBuffer {
   public:
    struct Attachments {
        enum class Type {
            TEXTURE,
            BUFFER,
            NONE  ///< nothing
        };

        explicit Attachments(Type p_color = Type::BUFFER, int p_numColor = 1, Type p_depth = Type::BUFFER,
                             Type p_stencil = Type::NONE, Type p_stencil_depth = Type::NONE)
            : color{p_color},
              numColor{p_numColor},
              depth{p_depth},
              stencil{p_stencil},
              stencil_depth{p_stencil_depth} {}

        Type color;
        int numColor;
        Type depth;
        Type stencil;
        Type stencil_depth;
    };

    FrameBufferObject(int width, int height, int numSamples, Attachments attachments, bool isHDR = false)
        : BaseFrameBuffer{width, height, numSamples, isHDR} {
        initialize(attachments);
    }

   protected:
    void initialize(Attachments a);
};
}  // namespace daft::core