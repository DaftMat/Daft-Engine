//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <string>

namespace daft::core::utils {
class ENGINE_API IO {
   public:
    static std::string getStringFromFile(const std::string &path);
};
}  // namespace daft::core::utils