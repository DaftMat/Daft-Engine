//
// Created by mathis on 07/07/2020.
//
#include "IO.hpp"

#include <fstream>
#include <sstream>

#include "Logger.hpp"

namespace daft::core::utils {
std::string IO::getStringFromFile(const std::string &path) {
    std::string res;
    std::ifstream resFile;
    resFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        resFile.open(path);
        std::stringstream resStream;
        resStream << resFile.rdbuf();
        res = resStream.str();
        resFile.close();
    } catch (std::ifstream::failure &f) {
        core::utils::Logger::error() << "failed to load file " << path << ".\n";
    }
    return res;
}
}  // namespace daft::core::utils