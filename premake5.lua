workspace "Rebelle"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Rebelle/vendor/GLFW/include"

include "Rebelle/vendor/GLFW"


project "Rebelle"
	location "Rebelle"
	kind "SharedLib"
	language "C++"

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
		"%{prj.name}/src/**.png",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb_image",
		"%{IncludeDir.GLFW}"
	}

	links 
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RBL_PLATFORM_WINDOWS",
			"RBL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "RBL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RBL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RBL_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Rebelle/src"
	}

	links 
	{
		"Rebelle"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RBL_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "RBL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "RBL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "RBL_DIST"
		optimize "On"