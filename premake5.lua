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
group "Dependencies"
	include "Chromaria/vendor/GLFW"
	include "Chromaria/vendor/Glad"
	include "Chromaria/vendor/imgui"
group ""

project "Chromaria"
	location "Chromaria"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
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
		systemversion "latest"

		defines
		{
			"CM_PLATFORM_WINDOWS",
			"CM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CM_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Chromaria"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "CM_DIST"
		runtime "Release"
		optimize "on"
