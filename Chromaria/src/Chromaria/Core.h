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

#define BIT(x) (1 << x)