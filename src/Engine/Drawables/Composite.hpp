//
// Created by mathis on 09/07/2020.
//
#pragma once
#include <API.hpp>
#include <memory>

#include "Drawable.hpp"

namespace daft::engine::objects {
class Composite : public Drawable {
   public:
    /**
     * Default constructor.
     */
    Composite() noexcept = default;

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
    void render() override;

    /**
     * Accepts a drawable visitor.
     * @param visitor - DrawableVisitor .
     */
    inline void accept(const DrawableVisitor *visitor) override;

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
};
}  // namespace daft::engine::objects