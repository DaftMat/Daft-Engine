//
// Created by mathis on 26/05/2020.
//
#pragma once
#include <spdlog/spdlog.h>

#include <API.hpp>
#include <memory>

namespace daft::core::utils {

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

}  // namespace daft::core::utils

/**
 * Macros using the Logger.
 */
#define ENGINE_ERROR(...)                                     \
    daft::core::utils::Log::engine()->error(__VA_ARGS__); \
    daft::core::utils::Log::engineConsole()->error(__VA_ARGS__)
#define ENGINE_INFO(...)                                     \
    daft::core::utils::Log::engine()->info(__VA_ARGS__); \
    daft::core::utils::Log::engineConsole()->info(__VA_ARGS__)
#define ENGINE_WARN(...)                                     \
    daft::core::utils::Log::engine()->warn(__VA_ARGS__); \
    daft::core::utils::Log::engineConsole()->warn(__VA_ARGS__)
#define ENGINE_TRACE(...)                                     \
    stardust::core::utils::Log::engine()->trace(__VA_ARGS__); \
    stardust::core::utils::Log::engineConsole()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...)                                     \
    stardust::core::utils::Log::engine()->debug(__VA_ARGS__); \
    stardust::core::utils::Log::engineConsole()->debug(__VA_ARGS__)

#define APP_ERROR(...)                                     \
    stardust::core::utils::Log::app()->error(__VA_ARGS__); \
    stardust::core::utils::Log::appConsole()->error(__VA_ARGS__)
#define APP_INFO(...)                                     \
    daft::core::utils::Log::app()->info(__VA_ARGS__); \
    daft::core::utils::Log::appConsole()->info(__VA_ARGS__)
#define APP_WARN(...)                                     \
    stardust::core::utils::Log::app()->warn(__VA_ARGS__); \
    stardust::core::utils::Log::appConsole()->warn(__VA_ARGS__)
#define APP_TRACE(...)                                     \
    stardust::core::utils::Log::app()->trace(__VA_ARGS__); \
    stardust::core::utils::Log::appConsole()->trace(__VA_ARGS__)
#define APP_DEBUG(...)                                     \
    stardust::core::utils::Log::app()->debug(__VA_ARGS__); \
    stardust::core::utils::Log::appConsole()->debug(__VA_ARGS__)