#pragma once
#include "Game.h"
#include "Menu.h"

// this class manages the big picture of the game
class GameManager
{
	static constexpr const char* SCREEN_FILE_NAME = "dkong_*.screen";

	std::vector<std::string> levelFileNames;
	// reads all the file names of the level file name template into a vector above  
	void readLevelFileNames();

public:
	//function has a loop that can only be broken by selecting EXIT in the menu, 
	// it allows to return to the menu after gameOver/win
	void launchGame();
};