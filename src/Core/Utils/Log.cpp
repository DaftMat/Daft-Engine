//
// Created by mathis on 26/05/2020.
//
#include "Log.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace daft::core::utils {

void Log::init(const std::string &engineLoggerName, const std::string &appLoggerName) {
    spdlog::set_pattern("%^> [%D][%T] -- %n::%l -- %v%$");
#if defined(DEBUG) && defined(TRACE)
    spdlog::set_level(spdlog::level::trace);
#elif defined(DEBUG)
    spdlog::set_level(spdlog::level::debug);
#elif defined(RELEASE)
    spdlog::set_level(spdlog::level::off);
#endif
    m_engineLogger = spdlog::basic_logger_mt(engineLoggerName, "logs/" + engineLoggerName + ".txt");
    m_appLogger = spdlog::basic_logger_mt(appLoggerName, "logs/" + appLoggerName + ".txt");
    m_engineConsole = spdlog::stdout_color_mt("ENGINE");
    m_appConsole = spdlog::stdout_color_mt("APP");
    ENGINE_INFO("Engine logger initialized.");
    APP_INFO("App logger initialized.");
    spdlog::set_pattern("%^> [%T] -- %n::%l -- %v%$");
}

std::shared_ptr<spdlog::logger> Log::m_engineLogger{nullptr};
std::shared_ptr<spdlog::logger> Log::m_appLogger{nullptr};
std::shared_ptr<spdlog::logger> Log::m_engineConsole{nullptr};
std::shared_ptr<spdlog::logger> Log::m_appConsole{nullptr};

}  // namespace daft::core::utils