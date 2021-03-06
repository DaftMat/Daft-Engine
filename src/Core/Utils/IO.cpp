//
// Created by mathis on 07/07/2020.
//
#include "IO.hpp"

#include <fstream>
#include <sstream>

#include "Logger.hpp"

namespace daft::core {
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
        std::stringstream ss;
        ss << "failed to load file " << path << "\n" << f.what();
        core::Logger::error(std::move(ss));
    }
    return res;
}
}  // namespace daft::core