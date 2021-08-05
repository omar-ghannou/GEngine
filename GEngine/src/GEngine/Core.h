#pragma once

#ifdef GE_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GE_API __declspec(dllexport)
	#else
		#define GE_API __declspec(dllimport)
	#endif // G_BUILD_DLL
#else
	#error This version of GEngine only supports Windows
#endif // G_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
