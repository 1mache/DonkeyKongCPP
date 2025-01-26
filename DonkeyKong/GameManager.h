#pragma once

#include "Game.h"
#include "Menu.h"

class GameManager
{	
public:
	enum GameMode {STANDARD, SAVE, LOAD};
private:
	// by default it is just a standard game (like Ex 2)
	GameMode mode = STANDARD;
	std::vector<std::string> levelFileNames;

public:
	void setMode(GameMode newMode) 
	{
		mode = newMode;
	}
	
	//function has a loop that can only be broken by selecting EXIT in the menu, 
	// it allows to return to the menu after gameOver/win
	void launchGame();
};