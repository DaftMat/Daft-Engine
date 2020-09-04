//
// Created by mathis on 02/09/2020.
//
#include "ObjectRenderer.hpp"

namespace daft::engine {
void ObjectRenderer::render(daft::engine::Drawable *d) {
    if (d->isObject() || d->isComposite()) {
        PassRenderer::render(d);
    }
}
}  // namespace daft::engine