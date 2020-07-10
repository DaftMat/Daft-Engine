//
// Created by mathis on 09/07/2020.
//
#pragma once
#include <API.hpp>
#include <memory>

#include "Drawable.hpp"

namespace daft::core::geometry {
class ShaderProgram;
}

namespace daft::engine::objects {
class Composite : public Drawable {
   public:
    /**
     * Standard constructor
     * @param composite - parent.
     */
    explicit Composite(Composite *parent = nullptr,
                       std::string name = "Group" + std::to_string(m_nrComposite++)) noexcept;

    /**
     * Default move constructor.
     */
    Composite(Composite &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Composite &operator=(Composite &&) noexcept = default;

    /**
     * Renders all the Drawable within the composite.
     */
    void render(const Shader &shader) override;

    /**
     * Accepts a drawable visitor.
     * @param visitor - DrawableVisitor .
     */
    inline void accept(const DrawableVisitor *visitor) override;

    /**
     * Adds a drawable to the composite.
     * @param drawable
     */
    inline void add(Drawable *drawable);

    /**
     * Drawables reference
     * @return drawables ref.
     */
    auto &drawables() { return m_drawables; }

    /**
     * Drawables constant reference.
     * @return drawables const ref.
     */
    [[nodiscard]] const auto &drawbles() const { return m_drawables; }

   private:
    using DrawablePtr = std::shared_ptr<Drawable>;

    std::vector<DrawablePtr> m_drawables;

    static int m_nrComposite;
};
}  // namespace daft::engine::objects