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
class Torus;
// lights
class PointLight;
// composite
class Composite;
}  // namespace engine

namespace core {

/**
 * Base visitor class for all drawables
 */
class ENGINE_API DrawableVisitor {
   public:
    /**
     * Default ctor.
     */
    DrawableVisitor() = default;

    /**
     * Default move ctor.
     */
    DrawableVisitor(DrawableVisitor &&) = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    DrawableVisitor &operator=(DrawableVisitor &&) = default;

    /// OBJECTS

    /**
     * Visits an Object .
     */
    virtual void visit(engine::Object *) {}

    /**
     * Visits a Sphere .
     */
    virtual void visit(engine::Sphere *) {}

    /**
     * Visits a Torus .
     */
    virtual void visit(engine::Torus *) {}

    /// LIGHTS

    /**
     * Visits a PointLight .
     */
    virtual void visit(engine::PointLight *) {}

    /// GROUP

    /**
     * Visits a Composite .
     */
    virtual void visit(engine::Composite *);
};

}  // namespace core
}  // namespace daft