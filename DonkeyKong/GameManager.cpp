#include "GameManager.h"

std::unique_ptr<Game> GameManager::createGameBasedOnMode(GameMode mode, bool isSilent)
{
	Game* game = nullptr;
	if (mode == LOAD)
		game = new ReplayGame(levelFileNames);
	else
		game = new Game(levelFileNames, startLevelId, mode == SAVE);

	// we can do this from here because we`re a friend
	GameOptions::isInLoadMode = (mode == LOAD);
	GameOptions::isInSilentMode = isSilent;

	return std::unique_ptr<Game>(game);
}

void GameManager::launchGame(GameMode mode, bool isSilent)
{
	// hide cursor
	DK_utils::ShowConsoleCursor(false);
	DK_utils::clearScreen();

	DK_utils::readFileNames(levelFileNames, GameOptions::LEVEL_FILE_EXT, GameOptions::LEVELS_PATH);

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

		std::unique_ptr<Game> game = createGameBasedOnMode(mode, isSilent);

		// returns true if player lost
		bool gameOver = game->start();

		if (mode == LOAD)
		{
			DK_utils::clearScreen();
			std::cout << "End of recording." << std::endl;
			break;
		}
		else
		{
			if (gameOver)
			{
				DK_utils::clearScreen();
				menu.displayGameOver();
			}
			else
			{
				DK_utils::clearScreen();
				menu.displayWinScreen(game->getScore());
			}
		}
	}

	// show cursor again in the end(in case we`re running from cmd)
	DK_utils::ShowConsoleCursor(true);
}