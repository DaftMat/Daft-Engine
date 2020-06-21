//
// Created by mathis on 26/05/2020.
//
#pragma once
#include <spdlog/spdlog.h>

#include <API.hpp>
#include <memory>

namespace stardust::core {

/**
 * Logger class.
 * Given a string, you can print to the console and the log file.
 */
class ENGINE_API Log {
   public:
    /**
     * Initialize the logger, creating logging files.
     * @param engineLoggerName - name of the logger used in the engine.
     * @param appLoggerName - name of the logger used in the application
     * (abstraction using the engine).
     */
    static void init(const std::string &engineLoggerName = "engine_logs",
                     const std::string &appLoggerName = "app_logs");

    /**
     * Engine File Logger getter.
     * @return Engine logger.
     */
    static auto engine() { return m_engineLogger; }

    /**
     * Application File Logger getter.
     * @return App logger.
     */
    static auto app() { return m_appLogger; }

    /**
     * Engine Console Logger getter.
     * @return Engine logger.
     */
    static auto engineConsole() { return m_engineConsole; }

    /**
     * Application Console Logger getter.
     * @return App logger.
     */
    static auto appConsole() { return m_appConsole; }

   private:
    static std::shared_ptr<spdlog::logger> m_engineLogger;
    static std::shared_ptr<spdlog::logger> m_appLogger;
    static std::shared_ptr<spdlog::logger> m_engineConsole;
    static std::shared_ptr<spdlog::logger> m_appConsole;
};

}  // namespace stardust::core

/**
 * Macros using the Logger.
 */
#define ENGINE_ERROR(...)                              \
    stardust::core::Log::engine()->error(__VA_ARGS__); \
    stardust::core::Log::engineConsole()->error(__VA_ARGS__)
#define ENGINE_INFO(...)                              \
    stardust::core::Log::engine()->info(__VA_ARGS__); \
    stardust::core::Log::engineConsole()->info(__VA_ARGS__)
#define ENGINE_WARN(...)                              \
    stardust::core::Log::engine()->warn(__VA_ARGS__); \
    stardust::core::Log::engineConsole()->warn(__VA_ARGS__)
#define ENGINE_TRACE(...)                              \
    stardust::core::Log::engine()->trace(__VA_ARGS__); \
    stardust::core::Log::engineConsole()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...)                              \
    stardust::core::Log::engine()->debug(__VA_ARGS__); \
    stardust::core::Log::engineConsole()->debug(__VA_ARGS__)

#define APP_ERROR(...)                              \
    stardust::core::Log::app()->error(__VA_ARGS__); \
    stardust::core::Log::appConsole()->error(__VA_ARGS__)
#define APP_INFO(...)                              \
    stardust::core::Log::app()->info(__VA_ARGS__); \
    stardust::core::Log::appConsole()->info(__VA_ARGS__)
#define APP_WARN(...)                              \
    stardust::core::Log::app()->warn(__VA_ARGS__); \
    stardust::core::Log::appConsole()->warn(__VA_ARGS__)
#define APP_TRACE(...)                              \
    stardust::core::Log::app()->trace(__VA_ARGS__); \
    stardust::core::Log::appConsole()->trace(__VA_ARGS__)
#define APP_DEBUG(...)                              \
    stardust::core::Log::app()->debug(__VA_ARGS__); \
    stardust::core::Log::appConsole()->debug(__VA_ARGS__)