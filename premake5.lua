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
IncludeDir["Glad"] = "Rebelle/vendor/Glad/include"
IncludeDir["IMGUI"] = "Rebelle/vendor/IMGUI/include"
IncludeDir["GLM"] = "Rebelle/vendor/GLM"

include "Rebelle/vendor/GLFW"
include "Rebelle/vendor/Glad"
include "Rebelle/vendor/IMGUI"

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
		"%{prj.name}/vendor/GLM/glm/**.hpp",
		"%{prj.name}/vendor/GLM/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/stb_image",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.IMGUI}",
		"%{IncludeDir.GLM}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"IMGUI",		
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"RBL_PLATFORM_WINDOWS",
			"RBL_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_IMPL_OPENGL_LOADER_GLAD"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "RBL_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "RBL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "RBL_DIST"
		buildoptions "/MD"
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
		"Rebelle/src",
		"%{IncludeDir.GLM}"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "RBL_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "RBL_DIST"
		buildoptions "/MD"
		optimize "On"