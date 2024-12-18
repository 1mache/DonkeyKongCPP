#include "GameManager.h"

void GameManager::launchGame()
{
	ShowConsoleCursor(false);

	while (true)
	{
		Menu menu;

		//returns true if the user chose the exit option in the menu
		bool exitflag = menu.displayMainMenu();
		if (exitflag)
		{
			break; // player chose exit in menu, exit game
		}

		Game game;

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