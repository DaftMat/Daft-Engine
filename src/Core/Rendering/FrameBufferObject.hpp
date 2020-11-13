//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>

#include "BaseFrameBuffer.hpp"

namespace daft::core {
class FrameBufferObject : public BaseFrameBuffer {
   public:
    /**
     * Settings of a framebuffer,
     */
    struct Attachments {
        enum class Type {
            TEXTURE,
            BUFFER,
            NONE  ///< nothing
        };

        /**
         * Standard Constructor.
         * @param p_color - type of the color attachments.
         * @param p_numColor - number of color attachments.
         * @param p_depth - type of the depth attachment.
         * @param p_stencil - type of the stencil attachment.
         * @param p_stencil_depth - type of the depth_stencil attachment.
         */
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

    /**
     * Standard constructor.
     * @param width - width of the framebuffer.
     * @param height - height of the framebuffer.
     * @param numSamples - number of samples in the framebuffer.
     * @param attachments - settings of the framebuffer - see Attachments .
     * @param isHDR - if true, color buffers or textures will use GL_RGB16F.
     */
    FrameBufferObject(int width, int height, int numSamples, Attachments attachments, bool isHDR = false)
        : BaseFrameBuffer{width, height, numSamples, isHDR}, m_attachments{attachments} {
        initialize(attachments);
    }

    /**
     * Size setter
     * @param width - new width.
     * @param height - new height.
     */
    void setSize(int width, int height);

   protected:
    void initialize(Attachments a);

   private:
    Attachments m_attachments;
};
}  // namespace daft::core