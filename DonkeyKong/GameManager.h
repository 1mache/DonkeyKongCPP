#pragma once

#include "Game.h"
#include "ReplayGame.h"
#include "Menu.h"

class GameManager
{	
public:
	enum GameMode {STANDARD, SAVE, LOAD};
private:
	// by default it is just a standard game (like Ex 2)
	GameMode mode = STANDARD;
	std::vector<std::string> levelFileNames;
	int startLevelId = 0;

	std::unique_ptr<Game> createGameBasedOnMode(GameMode mode);
public:
	
	//function has a loop that can only be broken by selecting EXIT in the menu, 
	// it allows to return to the menu after gameOver/win
	void launchGame(GameMode mode, bool isSilent = false);
};