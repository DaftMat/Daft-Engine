//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>

namespace daft {
/// forward declarations
namespace engine {
// objects
class Object;
class Sphere;
// lights

// composite
class Composite;
}  // namespace engine

namespace core {

/**
 * Base visitor class for all drawables
 */
class ENGINE_API DrawableVisitor {
   public:
    DrawableVisitor() = default;

    DrawableVisitor(DrawableVisitor &&) = default;

    DrawableVisitor &operator=(DrawableVisitor &&) = default;

    /**
     * Visits an Object .
     */
    virtual void visit(engine::Object *) {}

    /**
     * Visits a Sphere .
     */
    virtual void visit(engine::Sphere *) {}

    /**
     * Visits a Composite .
     */
    virtual void visit(engine::Composite *);
};

}  // namespace core
}  // namespace daft