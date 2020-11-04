project "Imgui"
    kind "StaticLib"
	language "C++"
	cppdialect "C++17"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
files
	{
        "include/imconfig.h",
        "include/imgui.h",
        "include/imstb_rectpack.h",
        "include/imstb_textedit.h",
        "include/imstb_truetype.h",
		"include/imgui_internal.h",
        "src/imgui.cpp",
        "src/imgui_draw.cpp",      
        "src/imgui_widgets.cpp",
        "src/imgui_demo.cpp"
    }
    
    includedirs
    {
        "include"
    }

	filter "system:windows"
        systemversion "latest"
        staticruntime "On"
		cppdialect "C++17"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
