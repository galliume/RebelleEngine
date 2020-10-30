#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Rebelle
{
	class REBELLE_API Log
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

#define RBL_CORE_FATAL(...) ::Rebelle::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define RBL_CORE_ERROR(...) ::Rebelle::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RBL_CORE_WARN(...) ::Rebelle::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RBL_CORE_INFO(...) ::Rebelle::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RBL_CORE_TRACE(...) ::Rebelle::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define RBL_FATAL(...) ::Rebelle::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define RBL_ERROR(...) ::Rebelle::Log::GetClientLogger()->error(__VA_ARGS__)
#define RBL_WARN(...) ::Rebelle::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RBL_INFO(...) ::Rebelle::Log::GetClientLogger()->info(__VA_ARGS__)
#define RBL_TRACE(...) ::Rebelle::Log::GetClientLogger()->trace(__VA_ARGS__)