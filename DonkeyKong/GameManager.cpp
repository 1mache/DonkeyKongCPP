#include "GameManager.h"

void GameManager::launchGame()
{
	// hide cursor
	ShowConsoleCursor(false);

	readLevelFileNames();
	//if(levelFileNames.size() == 0)
	//{
	//    display error
	//}

	while (true)
	{	
		Menu menu(levelFileNames);

		//returns true if the user chose the exit option in the menu
		bool exitflag = menu.displayMainMenu();
		if (exitflag)
		{
			break; // player chose exit in menu, exit game
		}

		Game game(levelFileNames, menu.getChosenLevelId());

		bool gameOver;
		try
		{
			// returns true if player lost
			 gameOver = game.start();
		}
		catch (const LevelFileException& ex)
		{
			std::cout << ex.what();
			break;
		}

		if (gameOver)
		{
			clearScreen();
			menu.displayGameOver();
		}
		else
		{
			clearScreen();
			menu.displayWinScreen();
		}
	}
}

void GameManager::readLevelFileNames()
{
	// the dir iteration code was taken from here:
	// https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
	// and changed to some extent

	// using regex: https://www.geeksforgeeks.org/how-to-match-a-pattern-in-a-string-in-cpp/

	std::regex pattern(LEVEL_FILENAME_TEMPLATE);

	namespace fs = std::filesystem;
	std::string path = fs::current_path().string();

	for (const auto& entry : fs::directory_iterator(path))
	{
		std::string filename = entry.path().filename().string();
		//if filename matches the pattern
		if (std::regex_match(filename, pattern))
			levelFileNames.push_back(filename); // push it to the vector
	}
}