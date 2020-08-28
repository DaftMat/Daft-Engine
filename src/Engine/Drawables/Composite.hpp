//
// Created by mathis on 09/07/2020.
//
#pragma once
#include <API.hpp>
#include <memory>

#include "Drawable.hpp"

namespace daft::core {
class ShaderProgram;
}

namespace daft::engine {
class ENGINE_API Composite : public Drawable {
   public:
    /**
     * Standard constructor
     * @param composite - parent.
     */
    explicit Composite(Composite *parent = nullptr,
                       std::string name = "Group" + std::to_string(m_nrComposite++)) noexcept;

    ~Composite() noexcept override = default;

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
     * Does nothing. Have to pass through a RendererVisitor that will render all the objects within.
     * Because of the variation of shaders.
     */
    void render(const core::ShaderProgram &shader) override;

    /**
     * Accepts a drawable visitor.
     * @param visitor - DrawableVisitor .
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Adds a drawable to the composite.
     * @param drawable - drawable to add.
     */
    void add(Drawable *drawable);

    /**
     * Drawables reference
     * @return drawables ref.
     */
    auto &drawables() { return m_drawables; }

    /**
     * Drawables constant reference.
     * @return drawables const ref.
     */
    [[nodiscard]] const auto &drawables() const { return m_drawables; }

    void reset() override;

   private:
    using DrawablePtr = std::shared_ptr<Drawable>;

    std::vector<DrawablePtr> m_drawables;

    static int m_nrComposite;
};
}  // namespace daft::engine