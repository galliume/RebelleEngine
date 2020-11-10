#pragma once

#ifdef RBL_PLATFORM_WINDOWS
#if RBL_DYNAMIC_LINK
	#ifdef RBL_BUILD_DLL
		#define REBELLE_API __declspec(dllexport)
	#else
		#define REBELLE_API __declspec(dllimport)
	#endif
#else
#define REBELLE_API
#endif
#else
	#error Rebelle only support Windows.
#endif

#define BIT(x) (1 << x)

#ifdef RBL_ENABLE_ASSERTS
#define RBL_ASSERT(x, ...) { if(!(x)) { RBL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define RBL_CORE_ASSERT(x, ...) { if(!(x)) { RBL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define RBL_ASSERT(x, ...)
#define RBL_CORE_ASSERT(x, ...)
#endif