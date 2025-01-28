#include "Constants.h"

// static member definitions
bool Constants::isInSilentMode = false;
bool Constants::isInLoadMode = false;

int Constants::getRefreshRate()
{
	if (isInSilentMode) 
		return 0;
	else if (isInLoadMode) 
		return GAME_REFRESH_RATE / 2;
	else 
		return GAME_REFRESH_RATE;
}
