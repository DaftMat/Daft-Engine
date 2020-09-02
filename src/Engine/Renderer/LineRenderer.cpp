//
// Created by mathis on 02/09/2020.
//
#include "LineRenderer.hpp"

namespace daft::engine {
void LineRenderer::render(daft::engine::Drawable *d) {
    if (d->selected()) {
        if (d->isComposite()) {
            shader()->setVec3("color", glm::vec3{0.7f, 0.1f, 0.11f});
        } else {
            shader()->setVec3("color", glm::vec3{1.f, 0.15f, 0.16f});
        }
    } else if (d->isLight()) {
        shader()->setVec3("color", glm::vec3{1.f});
    } else {  // regular unselected objects
        shader()->setVec3("color", glm::vec3{0.f});
    }
    PassRenderer::render(d);
}
}  // namespace daft::engine