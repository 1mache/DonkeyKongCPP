#include "GameOptions.h"

bool GameOptions::isInLoadMode = false;
bool GameOptions::isInSilentMode = false;

bool GameOptions::isSilentModeOn()
{
	return isInSilentMode;
}

int GameOptions::getRefreshRate()
{
	if (isInSilentMode) 
		return 0;
	else if (isInLoadMode) 
		return GAME_REFRESH_RATE / 2;
	else 
		return GAME_REFRESH_RATE;
}
