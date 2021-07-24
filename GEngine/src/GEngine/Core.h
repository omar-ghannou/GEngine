#pragma once

#ifdef G_PLATFORM_WINDOWS
	#ifdef G_BUILD_DLL
		#define G_API __declspec(dllexport)
	#else
		#define G_API __declspec(dllimport)
	#endif // G_BUILD_DLL
#else
	#error This version of GEngine only supports Windows
#endif // G_PLATFORM_WINDOWS
