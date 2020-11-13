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
    /**
     * Standard constructor.
     */
    QuadRenderer();

    /**
     * Prepares the quads to be rendered.
     */
    void prepare() const;

    /**
     * Renders the quads
     */
    void render() const;

    /**
     * Adds a quad given its settings.
     * @param x - x origin position of the quad.
     * @param y - y origin position of the quad.
     * @param width - width of the quad.
     * @param height - height of the quad.
     */
    void addQuad(int x, int y, int width, int height) { m_quads.emplace_back(x, y, width, height); }

    /**
     * Inner Quad getter.
     * @param i - index of the quad.
     * @return - quads[i].
     */
    Quad &quad(int i) { return m_quads[i]; }

   private:
    std::shared_ptr<core::ShaderProgram> m_shader{nullptr};
    std::vector<Quad> m_quads{};
};
}  // namespace daft::engine