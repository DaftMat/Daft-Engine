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
class BSpline2D;
class Cylinder;
class Metaballs;
class Caves;
// lights
class PointLight;
class SpotLight;
class DirLight;
class QuadLight;
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
     * Visits a BSpline2D .
     */
    virtual void visit(engine::BSpline2D *) {}

    /**
     * Visits a Cylinder .
     */
    virtual void visit(engine::Cylinder *) {}

    /**
     * Visits an Metaballs .
     */
    virtual void visit(engine::Metaballs *) {}

    /**
     * Visits an Metaballs .
     */
    virtual void visit(engine::Caves *) {}

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

    /**
     * Visits a QuadLight .
     */
    virtual void visit(engine::QuadLight *) {}

    /// GROUP

    /**
     * Visits a Composite .
     */
    virtual void visit(engine::Composite *);
};

}  // namespace core
}  // namespace daft