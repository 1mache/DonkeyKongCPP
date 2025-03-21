workspace "DonkeyKongConsole"
	configurations { "Debug", "Release" }

project "DonkeyKong"
	kind "ConsoleApp"
	language "C++"
	location "DonkeyKong/"
	files{
		"*.h",
		"*.cpp"
	}

	-- Copy the entire "levels", "recordings" directories into the targetdir after each build
	postbuildcommands {
        "{COPYDIR} levels %{cfg.targetdir}/levels",
        "{COPYDIR} recordings %{cfg.targetdir}/recordings",
    }

	filter ("configurations:Debug")
		defines{"DEBUG"}
		targetdir "/bin/debug"

	filter ("configurations:Release")
		optimize "On"
		targetdir "/bin/release"