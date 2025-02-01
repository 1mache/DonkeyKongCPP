#pragma once

#include "Point.h"

class GameOptions
{
	//constants that a bunch of classes need
private:
	static constexpr int GAME_REFRESH_RATE = 75;
	static bool isInSilentMode;
	static bool isInLoadMode;

	GameOptions() = default;
	GameOptions(GameOptions& other) = delete;
	void operator=(const GameOptions& other) = delete;

public:
	static constexpr int SCREEN_WIDTH = 80;
	static constexpr int SCREEN_HEIGHT = 25;
	static constexpr Point POS_NOT_SET = { -1 , -1 };
	static constexpr Point POINT_ZERO = { 0 , 0 };
	static constexpr char KEY_NOT_SET = 0;

	// prefix of our filenames
	static constexpr const char* FILENAME_PREFIX = "dkong_";
	// extensions of filenames used by the game
	static constexpr const char* LEVEL_FILE_EXT = ".screen";
	static constexpr const char* STEPS_FILE_EXT = ".steps";
	static constexpr const char* RESULTS_FILE_EXT = ".result";


	static void setSilentMode(bool enabled)
	{
		isInSilentMode = enabled;
	}

	static void setLoadMode(bool enabled)
	{
		isInLoadMode = enabled;
	}

	static bool isSilentModeOn()
	{
		return isInSilentMode;
	}

	// we wants no sleeps while in test mode and half the sleep in load mode
	static int getRefreshRate();
};