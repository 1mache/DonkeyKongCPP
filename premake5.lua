workspace "DonkeyKongConsole"
	configurations { "Debug", "Release" }
	platforms { "Win32" ,"Win64" } 
	location "DonkeyKong/" -- where the project files will sit

project "DonkeyKong"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	files {
		"DonkeyKong/**.h",
		"DonkeyKong/**.cpp",
		"levels/**",
		"recordings/**"
	}

	-- Set up filters in Visual Studio:
    vpaths {
        ["Header Files"] = { "DonkeyKong/**.h" },
        ["Source Files"] = { "DonkeyKong/**.cpp" },
		["Resource Files/Levels"] = { "levels/**"},
		["Resource Files/Recordings"] = { "recordings/**"}
    }

	-- Copy the entire "levels", "recordings" directories into the targetdir after each build
	postbuildcommands {
		"{MKDIR} %{cfg.targetdir}/levels",
    	"{MKDIR} %{cfg.targetdir}/recordings",
        "{COPYDIR} ../levels %{cfg.targetdir}/levels",
        "{COPYDIR} ../recordings %{cfg.targetdir}/recordings"
    }

	filter ("configurations:Debug")
		defines{"DEBUG"}
		targetdir "bin/debug"

	filter ("configurations:Release")
		optimize "On"
		targetdir "bin/release"