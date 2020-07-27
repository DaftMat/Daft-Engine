//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>

namespace daft {
/// forward declarations
namespace engine::objects {
class Object;
class Composite;
}  // namespace engine::objects

namespace core::utils {
using namespace engine::objects;

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
    virtual void visit(Object *) {}

    /**
     * Visits a Composite .
     */
    virtual void visit(Composite *);
};

}  // namespace core::utils
}  // namespace daft