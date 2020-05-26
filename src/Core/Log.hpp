//
// Created by mathis on 26/05/2020.
//
#pragma once
#include <API.hpp>
#include <memory>

#include <spdlog/spdlog.h>

class ENGINE_API Log {
public:
    static void init(const std::string &engineLoggerName = "engine_logs", const std::string &appLoggerName = "app_logs");

    static std::shared_ptr<spdlog::logger> engine() { return m_engineLogger; }
    static std::shared_ptr<spdlog::logger> app() { return m_appLogger; }

    static std::shared_ptr<spdlog::logger> engineConsole() { return m_engineConsole; }
    static std::shared_ptr<spdlog::logger> appConsole() { return m_appConsole; }

private:
    static std::shared_ptr<spdlog::logger> m_engineLogger;
    static std::shared_ptr<spdlog::logger> m_appLogger;
    static std::shared_ptr<spdlog::logger> m_engineConsole;
    static std::shared_ptr<spdlog::logger> m_appConsole;
};



#define ENGINE_ERROR(...)               \
    Log::engine()->error(__VA_ARGS__);  \
    Log::engineConsole()->error(__VA_ARGS__)
#define ENGINE_INFO(...)                \
    Log::engine()->info(__VA_ARGS__);   \
    Log::engineConsole()->info(__VA_ARGS__)
#define ENGINE_WARN(...)                \
    Log::engine()->warn(__VA_ARGS__);   \
    Log::engineConsole()->warn(__VA_ARGS__)
#define ENGINE_TRACE(...)               \
    Log::engine()->trace(__VA_ARGS__);  \
    Log::engineConsole()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...)               \
    Log::engine()->debug(__VA_ARGS__);  \
    Log::engineConsole()->debug(__VA_ARGS__)

#define APP_ERROR(...)               \
    Log::app()->error(__VA_ARGS__);  \
    Log::appConsole()->error(__VA_ARGS__)
#define APP_INFO(...)                \
    Log::app()->info(__VA_ARGS__);   \
    Log::appConsole()->info(__VA_ARGS__)
#define APP_WARN(...)                \
    Log::app()->warn(__VA_ARGS__);   \
    Log::appConsole()->warn(__VA_ARGS__)
#define APP_TRACE(...)               \
    Log::app()->trace(__VA_ARGS__);  \
    Log::appConsole()->trace(__VA_ARGS__)
#define APP_DEBUG(...)               \
    Log::app()->debug(__VA_ARGS__);  \
    Log::appConsole()->debug(__VA_ARGS__)
