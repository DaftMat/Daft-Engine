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
/**
 * A Drawable that represents a group of drawables.
 */
class ENGINE_API Composite : public Drawable {
   public:
    /**
     * Standard constructor
     * @param composite - parent.
     */
    explicit Composite(Composite *parent = nullptr,
                       std::string name = "Group" + std::to_string(m_nrComposite++)) noexcept;

    /**
     * Default destructor.
     */
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
     * renders the edges only of the inner geometry.
     * @param shader - shader to render with.
     */
    void renderEdges(const core::ShaderProgram &shader) override;

    /**
     * Accepts a drawable visitor.
     * @param visitor - DrawableVisitor .
     */
    void accept(DrawableVisitor *visitor) override;

    /**
     * Object accessor.
     * This version is recursive.
     * @param name - name of the object we're looking for.
     * @return the object if it's the right name. nullptr otherwise.
     */
    Drawable *find(const std::string &name) override;

    /**
     * Adds a drawable to the composite.
     * @param drawable - drawable to add.
     */
    void add(std::shared_ptr<Drawable> drawable);

    /**
     * Removes a drawable from the composite and the engine.
     * @param name - name of the drawable to be deleted.
     */
    bool remove(const std::string &name) override;

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

    /**
     * Resets all the drawables inside this.
     */
    void reset() override;

    /**
     * updates all the drawables inside this.
     */
    void update() override;

    /**
     * Tests if this is a Composite .
     * @return true.
     */
    [[nodiscard]] bool isComposite() const override { return true; }

    /**
     * Tests if this is an Object .
     * @return false.
     */
    [[nodiscard]] bool isObject() const override { return false; }

    /**
     * Tests if this is a Light .
     * @return false.
     */
    [[nodiscard]] bool isLight() const override { return false; }

    /**
     * Gets the type of drawable.
     * @return Type::Group .
     */
    Type getType() override { return Type::Group; }

   private:
    using DrawablePtr = std::shared_ptr<Drawable>;

    std::vector<DrawablePtr> m_drawables;

    static int m_nrComposite;
};
}  // namespace daft::engine