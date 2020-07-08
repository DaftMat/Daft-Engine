//
// Created by mathis on 08/07/2020.
//
#pragma once
#include <API.hpp>

namespace daft {
/// forward declarations
namespace engine::objects {
class Object;
}  // namespace engine::objects

namespace core::utils {
using namespace engine::objects;

/**
 * Base visitor class for all drawables
 */
class ENGINE_API DrawableVisitor {
   public:
    /**
     * Visits an Object .
     */
    virtual void visit(Object *) const = 0;
};

}  // namespace core::utils
}  // namespace daft