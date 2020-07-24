//
// Created by mathis on 24/07/2020.
//
#pragma once
#include <API.hpp>

namespace daft::core::utils {
/**
 * Base class for the design pattern Command.
 */
class ENGINE_API BaseCommand {
   public:
    /**
     * executes the command.
     */
    virtual void execute() = 0;
};
}  // namespace daft::core::utils