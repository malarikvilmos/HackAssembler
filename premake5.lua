workspace "HackAssembler"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "HackAssembler"
    location "HackAssembler"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.c",
        "%{prj.name}/src/**.cpp"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        kind "ConsoleApp"

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines {"_DEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        kind "ConsoleApp"
        defines {"_NDEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
        runtime "Release"
        optimize "Full"

    filter "system:linux"
        cppdialect "C++20"
        staticruntime "On"
        kind "ConsoleApp"

    filter "configurations:Debug"
        kind "ConsoleApp"
        defines {"_DEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        kind "ConsoleApp"
        defines {"_NDEBUG", "_CONSOLE", "_CRT_SECURE_NO_WARNINGS"}
        runtime "Release"
        optimize "Full"

    

    filter {}

