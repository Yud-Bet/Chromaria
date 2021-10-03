#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Chromaria {

	class CHROMARIA_API Log
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

#define CM_CORE_ERROR(...)	Chromaria::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CM_CORE_WARN(...)	Chromaria::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CM_CORE_INFO(...)	Chromaria::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CM_CORE_TRACE(...)	Chromaria::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CM_CORE_FATAL(...)	Chromaria::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CM_ERROR(...)		Chromaria::Log::GetClientLogger()->error(__VA_ARGS__)
#define CM_WARN(...)		Chromaria::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CM_INFO(...)		Chromaria::Log::GetClientLogger()->info(__VA_ARGS__)
#define CM_TRACE(...)		Chromaria::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CM_FATAL(...)		Chromaria::Log::GetClientLogger()->critical(__VA_ARGS__)