workspace "GEngine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GEngine/vendors/GLFW/include"

include "GEngine/vendors/GLFW"

project "GEngine"
	location "GEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")

	pchheader "GEpch.h"
	pchsource "GEngine/src/GEpch.cpp"
	
	files{

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/GEngine/**.h",
		"%{prj.name}/src/GEngine/**.cpp",
		"%{prj.name}/src/GEngine/Events/**.h",
		"%{prj.name}/src/GEngine/Events/**.cpp",
		"%{prj.name}/src/Platform/Windows/**.h",
		"%{prj.name}/src/Platform/Windows/**.cpp",

	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendors/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-intermediate/" .. outputdir .. "/%{prj.name}")
	
	files{

		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"

	}

	includedirs {
		"GEngine/vendors/spdlog/include",
		"GEngine/src"
	}

	links{
		"GEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"GE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		optimize "On"
