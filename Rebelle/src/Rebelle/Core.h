#pragma once

#ifdef RBL_PLATFORM_WINDOWS
	#ifdef RBL_BUILD_DLL
		#define REBELLE_API __declspec(dllexport)
	#else
		#define REBELLE_API __declspec(dllimport)
	#endif
#else
	#error Rebelle only support Windows.
#endif