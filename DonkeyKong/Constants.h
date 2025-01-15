#pragma once

#include "Point.h"

class Constants
{
	//constants that a bunch of classes need
public:
	static constexpr int SCREEN_WIDTH = 80;
	static constexpr int SCREEN_HEIGHT = 25;
	static constexpr int GAME_REFRESH_RATE = 65;
	static constexpr Point POS_NOT_SET = { -1 , -1 };
	static constexpr Point POINT_ZERO = { 0 , 0 };
};