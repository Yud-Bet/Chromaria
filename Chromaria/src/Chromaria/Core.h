#pragma once

#ifdef CM_PLATFORM_WINDOWS
#ifdef CM_DYNAMIC_LINK
	#ifdef CM_BUILD_DLL
		#define CHROMARIA_API _declspec(dllexport)
	#else
		#define CHROMARIA_API _declspec(dllimport)
	#endif
#else
	#define CHROMARIA_API
#endif
#else
	#error Chormaria only support windows
#endif

#ifdef CM_DEBUG
	#define CM_ENABLE_ASSERTS
#endif

#ifdef CM_ENABLE_ASSERTS
	#define CM_ASSERTS(x, ...) { if (!(x)) { CM_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CM_CORE_ASSERTS(x, ...) { if (!(x)) { CM_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CM_ASSERTS(x, ...)
	#define CM_CORE_ASSERTS(x, ...)
#endif

#define BIT(x) (1 << x)

#define CM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)