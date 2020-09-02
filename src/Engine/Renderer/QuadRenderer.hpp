//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Rendering/ShaderProgram.hpp>
#include <memory>

#include "Quad.hpp"

namespace daft::engine {
class QuadRenderer {
   public:
    QuadRenderer();

    void prepare() const;

    void render() const;

    void addQuad(int x, int y, int width, int height) { m_quads.emplace_back(x, y, width, height); }

    Quad &quad(int i) { return m_quads[i]; }

   private:
    std::shared_ptr<core::ShaderProgram> m_shader{nullptr};
    std::vector<Quad> m_quads{};
};
}  // namespace daft::engine