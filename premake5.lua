workspace "Chromaria"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Chromaria/vendor/GLFW/include"
IncludeDir["Glad"] = "Chromaria/vendor/Glad/include"
IncludeDir["ImGui"] = "Chromaria/vendor/imgui"
IncludeDir["glm"] = "Chromaria/vendor/glm"

-- Include .lua file
include "Chromaria/vendor/GLFW"
include "Chromaria/vendor/Glad"
include "Chromaria/vendor/imgui"

project "Chromaria"
	location "Chromaria"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cmpch.h"
	pchsource "Chromaria/src/cmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"imgui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CM_PLATFORM_WINDOWS",
			"CM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
	filter "configurations:Debug"
		defines "CM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CM_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Chromaria/vendor/spdlog/include",
		"Chromaria/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Chromaria"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CM_DIST"
		runtime "Release"
		optimize "On"