//
// Created by mathis on 02/09/2020.
//
#include "ObjectRenderer.hpp"

namespace daft::engine {
void ObjectRenderer::render(daft::engine::Drawable *d) {
    if (d->isObject() || d->isComposite()) {
        shader()->setVec3("color", glm::vec3{0.f, 0.f, 1.f});
        PassRenderer::render(d);
    }
}
}  // namespace daft::engine