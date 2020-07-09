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

   private:
    using DrawablePtr = std::shared_ptr<Drawable>;

    std::vector<DrawablePtr> m_drawables;
};
}  // namespace daft::engine::objects