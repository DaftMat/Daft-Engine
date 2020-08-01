//
// Created by mathis on 01/08/2020.
//
#include "Logger.hpp"

#include <fstream>
#include <iostream>

namespace daft::core::utils {
Logger::Log Logger::m_log{"logs/logs.txt"};

Logger::Log &Logger::debug() {
    m_log << "> debug -- ";
    return m_log;
}

Logger::Log &Logger::info() {
    m_log << "> info -- ";
    return m_log;
}

Logger::Log &Logger::warn() {
    m_log << "> warn -- ";
    return m_log;
}

Logger::Log &Logger::trace() {
    m_log << "> trace -- ";
    return m_log;
}

Logger::Log &Logger::error() {
    m_log << "> error -- ";
    return m_log;
}

}  // namespace daft::core::utils