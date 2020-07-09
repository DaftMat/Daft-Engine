//
// Created by mathis on 09/07/2020.
//
#include "Composite.hpp"

namespace daft::engine::objects {
void Composite::render() {
    for (auto &d : m_drawables) {
        d->render();
    }
}
}  // namespace daft::engine::objects