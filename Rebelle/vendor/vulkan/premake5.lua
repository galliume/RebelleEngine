project "vulkan"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "Include/vulkan/*.h",
        "Lib/vulkan-1.lib"
    }

    includedirs {
        "Include"
    }
    
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"