#pragma once
#include "Game.h"
#include "Menu.h"

// this class manages the big picture of the game
class GameManager
{
public:
	//function has a loop that can only be broken by selecting EXIT in the menu, 
	// it allows to return to the menu after gameOver/win
	void launchGame();
};