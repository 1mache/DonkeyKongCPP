#pragma once

#include "Point.h"

class Constants
{
	//constants that a bunch of classes need
public:
	static constexpr int SCREEN_WIDTH = 80;
	static constexpr int SCREEN_HEIGHT = 25;
	static constexpr int GAME_REFRESH_RATE = 75;
	static constexpr Point POS_NOT_SET = { -1 , -1 };
	static constexpr Point POINT_ZERO = { 0 , 0 };
	static constexpr char KEY_NOT_SET = 0;

	// prefix of our filenames
	static constexpr const char* FILENAME_PREFIX = "dkong_";
	// extensions of filenames used by the game
	static constexpr const char* LEVEL_FILE_EXT = ".screen";
	static constexpr const char* STEPS_FILE_EXT = ".steps";
	static constexpr const char* RESULTS_FILE_EXT = ".result";
};