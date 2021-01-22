#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace EngineX
{
    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define EX_CORE_TRACE(...)    ::EngineX::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EX_CORE_INFO(...)     ::EngineX::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EX_CORE_WARN(...)     ::EngineX::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EX_CORE_ERROR(...)    ::EngineX::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EX_CORE_CRITICAL(...) ::EngineX::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define EX_TRACE(...)      ::EngineX::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EX_INFO(...)       ::EngineX::Log::GetClientLogger()->info(__VA_ARGS__)
#define EX_WARN(...)       ::EngineX::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EX_ERROR(...)      ::EngineX::Log::GetClientLogger()->error(__VA_ARGS__)
#define EX_CRITICAL(...)   ::EngineX::Log::GetClientLogger()->critical(__VA_ARGS__)