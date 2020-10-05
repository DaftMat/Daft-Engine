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
class Cube;
class BSpline;
class Cylinder;
// lights
class PointLight;
class SpotLight;
class DirLight;
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

    /**
     * Visits a Cube .
     */
    virtual void visit(engine::Cube *) {}

    /**
     * Visits a BSpline .
     */
    virtual void visit(engine::BSpline *) {}

    /**
     * Visits a Cylinder .
     */
    virtual void visit(engine::Cylinder *) {}

    /// LIGHTS

    /**
     * Visits a PointLight .
     */
    virtual void visit(engine::PointLight *) {}

    /**
     * Visits a SpotLight .
     */
    virtual void visit(engine::SpotLight *) {}

    /**
     * Visits a DirLight .
     */
    virtual void visit(engine::DirLight *) {}

    /// GROUP

    /**
     * Visits a Composite .
     */
    virtual void visit(engine::Composite *);
};

}  // namespace core
}  // namespace daft