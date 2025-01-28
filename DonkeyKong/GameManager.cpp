#include "GameManager.h"

std::unique_ptr<Game> GameManager::createGameBasedOnMode(GameMode mode)
{
	Constants::setLoadMode(false);
	Game* game = nullptr;
	if (mode == LOAD)
	{
		game = new ReplayGame(levelFileNames);
		Constants::setLoadMode(true);
	}
	else
		game = new Game(levelFileNames, startLevelId, mode == SAVE);

	return std::unique_ptr<Game>(game);
}

void GameManager::launchGame(GameMode mode)
{
	// hide cursor
	ShowConsoleCursor(false);
	// TODO: doesnt work from cmd
	clearScreen();
	readFileNames(levelFileNames, Constants::LEVEL_FILE_EXT);

	while (true)
	{	
		Menu menu(levelFileNames);
		if(mode != LOAD)
		{
			//returns true if the user chose the exit option in the menu
			bool exitflag = menu.displayMainMenu();
			startLevelId = menu.getChosenLevelId();

			if (exitflag)
			{
				break; // player chose exit in menu, exit game
			}
		}

		std::unique_ptr<Game> game = createGameBasedOnMode(mode);

		// returns true if player lost
		bool gameOver = game->start();

		if (mode == LOAD)
		{
			clearScreen();
			std::cout << "End of recording." << std::endl;
			break;
		}
		else
		{
			if (gameOver)
			{
				clearScreen();
				menu.displayGameOver();
			}
			else
			{
				clearScreen();
				menu.displayWinScreen(game->getScore());
			}
		}
	}
}