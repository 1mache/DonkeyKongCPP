#include "GameOptions.h"

// static member definitions
bool GameOptions::isInSilentMode = false;
bool GameOptions::isInLoadMode = false;

int GameOptions::getRefreshRate()
{
	if (isInSilentMode) 
		return 0;
	else if (isInLoadMode) 
		return GAME_REFRESH_RATE / 2;
	else 
		return GAME_REFRESH_RATE;
}
