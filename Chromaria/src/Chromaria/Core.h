#pragma once

#ifdef CM_PLATFORM_WINDOWS
	#ifdef CM_BUILD_DLL
		#define CHROMARIA_API _declspec(dllexport)
	#else
		#define CHROMARIA_API _declspec(dllimport)
	#endif
#else
	#error Chormaria only support windows
#endif

#ifdef CM_ENABLE_ASSERTS
	#define CM_ASSERTS(x, ...) { if (!(x)) { CM_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CM_CORE_ASSERTS(x, ...) { if (!(x)) { CM_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CM_ASSERTS(x, ...)
	#define CM_CORE_ASSERTS(x, ...)
#endif

#define BIT(x) (1 << x)