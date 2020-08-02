//
// Created by mathis on 01/08/2020.
//
#pragma once
#include <API.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace daft::core::utils {
class ENGINE_API Logger {
   public:
    static void debug(std::stringstream ss);

    static void info(std::stringstream ss);

    static void warn(std::stringstream ss);

    static void trace(std::stringstream ss);

    static void error(std::stringstream ss);

   private:
    static void createLogEntry(std::string type, std::string msg);

    static std::string getTimeStr();
};
}  // namespace daft::core::utils