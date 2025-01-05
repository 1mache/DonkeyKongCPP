#include "GameManager.h"

void GameManager::launchGame()
{
	// hide cursor
	ShowConsoleCursor(false);

	readLevelFileNames();

	while (true)
	{	
		Menu menu;

		//returns true if the user chose the exit option in the menu
		bool exitflag = menu.displayMainMenu();
		if (exitflag)
		{
			break; // player chose exit in menu, exit game
		}

		Game game(levelFileNames);

		// returns true if player lost
		bool gameOver = game.start();

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

}