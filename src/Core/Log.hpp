//
// Created by mathis on 26/05/2020.
//
#pragma once
#include <API.hpp>
#include <memory>

#include <spdlog/spdlog.h>

namespace ProjName::Core {

    class ENGINE_API Log {
    public:
        static void
        init(const std::string &engineLoggerName = "engine_logs", const std::string &appLoggerName = "app_logs");

        static auto engine() { return m_engineLogger; }

        static auto app() { return m_appLogger; }

        static auto engineConsole() { return m_engineConsole; }

        static auto appConsole() { return m_appConsole; }

    private:
        static std::shared_ptr<spdlog::logger> m_engineLogger;
        static std::shared_ptr<spdlog::logger> m_appLogger;
        static std::shared_ptr<spdlog::logger> m_engineConsole;
        static std::shared_ptr<spdlog::logger> m_appConsole;
    };

} // namespace ProjName::Core


#define ENGINE_ERROR(...)               \
    ProjName::Core::Log::engine()->error(__VA_ARGS__);  \
    ProjName::Core::Log::engineConsole()->error(__VA_ARGS__)
#define ENGINE_INFO(...)                \
    ProjName::Core::Log::engine()->info(__VA_ARGS__);   \
    ProjName::Core::Log::engineConsole()->info(__VA_ARGS__)
#define ENGINE_WARN(...)                \
    ProjName::Core::Log::engine()->warn(__VA_ARGS__);   \
    ProjName::Core::Log::engineConsole()->warn(__VA_ARGS__)
#define ENGINE_TRACE(...)               \
    ProjName::Core::Log::engine()->trace(__VA_ARGS__);  \
    ProjName::Core::Log::engineConsole()->trace(__VA_ARGS__)
#define ENGINE_DEBUG(...)               \
    ProjName::Core::Log::engine()->debug(__VA_ARGS__);  \
    ProjName::Core::Log::engineConsole()->debug(__VA_ARGS__)

#define APP_ERROR(...)               \
    ProjName::Core::Log::app()->error(__VA_ARGS__);  \
    ProjName::Core::Log::appConsole()->error(__VA_ARGS__)
#define APP_INFO(...)                \
    ProjName::Core::Log::app()->info(__VA_ARGS__);   \
    ProjName::Core::Log::appConsole()->info(__VA_ARGS__)
#define APP_WARN(...)                \
    ProjName::Core::Log::app()->warn(__VA_ARGS__);   \
    ProjName::Core::Log::appConsole()->warn(__VA_ARGS__)
#define APP_TRACE(...)               \
    ProjName::Core::Log::app()->trace(__VA_ARGS__);  \
    ProjName::Core::Log::appConsole()->trace(__VA_ARGS__)
#define APP_DEBUG(...)               \
    ProjName::Core::Log::app()->debug(__VA_ARGS__);  \
    ProjName::Core::Log::appConsole()->debug(__VA_ARGS__)