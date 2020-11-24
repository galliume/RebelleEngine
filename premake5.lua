workspace "Rebelle"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Rebelle/vendor/GLFW/include"
IncludeDir["Glad"] = "Rebelle/vendor/Glad/include"
IncludeDir["IMGUI"] = "Rebelle/vendor/IMGUI"
IncludeDir["GLM"] = "Rebelle/vendor/GLM"
IncludeDir["vulkan"] = "Rebelle/vendor/vulkan/include"

include "Rebelle/vendor/GLFW"
include "Rebelle/vendor/Glad"
include "Rebelle/vendor/IMGUI"
include "Rebelle/vendor/vulkan"

project "Rebelle"
	location "Rebelle"
 	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir  ("bin/" .. outputdir  .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir  .. "/%{prj.name}")

	pchheader "rblpch.h"
	pchsource "Rebelle/src/rblpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb_image",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.vulkan}"
	}

	links 
	{		
		"GLFW",
		"Glad",
		"IMGUI",
		"Rebelle/vendor/vulkan/Lib/vulkan-1.lib"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RBL_PLATFORM_WINDOWS",
			"RBL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "RBL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RBL_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "RBL_DIST"
		runtime "Release"
		symbols "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir  ("bin/" .. outputdir  .. "/%{prj.name}")
	objdir  ("bin-int/" .. outputdir  .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Rebelle/vendor/spdlog/include",
		"Rebelle/src",
		"Rebelle/vendor",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.vulkan}"
	}

	links 
	{
		"Rebelle",
		"GLFW",
		"Rebelle/vendor/vulkan/Lib/vulkan-1.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RBL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RBL_DEBUG"
		symbols "on"
		runtime "Debug"

	filter "configurations:Release"
		defines "RBL_RELEASE"
		optimize "on"
		runtime "Release"

	filter "configurations:Dist"
		defines "RBL_DIST"
		optimize "on"
		runtime "Release"