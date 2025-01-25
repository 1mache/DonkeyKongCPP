#pragma once

#include <filesystem>
#include <regex>

#include "Game.h"
#include "Menu.h"

// this class manages the big picture of the game
class GameManager
{
	//// string defining the pattern that we use to find level files. regular expression that means any 
	//// sequence of eng alphabet letters and digits after dkong_ that ends with .screen
	//static constexpr const char* LEVEL_FILENAME_TEMPLATE = "dkong_.+\\.screen";
	//// same for .steps files and .results files
	//static constexpr const char* STEPS_FILENAME_TEMPLATE = "dkong_.+\\.steps";
	//static constexpr const char* RESULT_FILENAME_TEMPLATE = "dkong_.+\\.result";
	
	std::vector<std::string> levelFileNames;
	// reads all the file names of the level file name template into a vector above  
	void readLevelFileNames();

public:
	//function has a loop that can only be broken by selecting EXIT in the menu, 
	// it allows to return to the menu after gameOver/win
	void launchGame();
};