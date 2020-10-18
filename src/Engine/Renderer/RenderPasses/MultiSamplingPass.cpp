//
// Created by mathis on 05/09/2020.
//
#include "MultiSamplingPass.hpp"

namespace daft::engine {
MultiSamplingPass::MultiSamplingPass(int width, int height, int numSample, bool isHDR)
    : m_fboIn{std::make_unique<core::FrameBufferObject>(width, height, numSample,
                                                        core::FrameBufferObject::Attachments{}, isHDR)},
      m_fboOut{std::make_unique<core::FrameBufferObject>(
          width, height, 1,
          core::FrameBufferObject::Attachments{core::FrameBufferObject::Attachments::Type::TEXTURE, 1,
                                               core::FrameBufferObject::Attachments::Type::TEXTURE},
          isHDR)} {}

void MultiSamplingPass::stop(int width, int height) const {
    m_fboIn->stop(width, height);
    m_fboIn->resolve(*m_fboOut);
}
}  // namespace daft::engine
