#include "Menu.h"

void Menu::print(const char* const screen[HEIGHT], int lineSleep) const
{
	for (int i = 0; i < HEIGHT - 1; i++) {
		std::cout << screen[i] << '\n';
		if(lineSleep > 0)
		{
			Sleep(lineSleep);
		}
	}
	std::cout << screen[HEIGHT - 1];
}

void Menu::update()
{
	flushInputBuffer();

	bool exitMenu = false;
	while (!exitMenu)
	{
		if (_kbhit())
		{
			char key = _getch();
			if(currentScreenId == MAIN_SCREEN_ID)
			{
				if(std::tolower(key) == KEYS[UP])
				{
					//erase arrow from prev position 
					eraseChar(MENU_OPTIONS[arrowId].screenPosition);
					arrowId = (arrowId - 1 + NUM_OF_OPTIONS) % NUM_OF_OPTIONS;
				}
				if(std::tolower(key) == KEYS[DOWN])
				{
					eraseChar(MENU_OPTIONS[arrowId].screenPosition);
					arrowId = (arrowId + 1) % NUM_OF_OPTIONS;
				}
			}

			//user pressed ENTER
			if(key == KEYS[SELECT])
			{
				//==========KEEP THIS VARUIABLE ???====================
				exitMenu = selectOption();
				if(exitMenu) 
				{
					break;
				}
			}
		}

		//move arrow if were on the main screen 
		if(currentScreenId == MAIN_SCREEN_ID)
		{
			drawChar(ARROW, MENU_OPTIONS[arrowId].screenPosition);
		}
			
		Sleep(Constants::GAME_REFRESH_RATE);
	}
}

bool Menu::selectOption()
{
	bool exitMenu = false;

	//if were on the control screen there is always a single option
	if (currentScreenId == CONTROL_SCREEN_ID)
	{
		clearScreen();
		gotoMainScreen();
		// control screen doesnt break the input loop
		return exitMenu;
	}

	if (currentScreenId == GAMEOVER_SCREEN_ID || currentScreenId == WIN_SCREEN_ID)
	{
		clearScreen();
		exitMenu = true;
		return exitMenu;
	}

	//if were on the main screen there is a bunch of options and the arrow tells us what we selected
	if (MENU_OPTIONS[arrowId] == CONTROLS_OPTION)
	{
		clearScreen();
		gotoControlScreen();
	}
	else if (MENU_OPTIONS[arrowId] == START_GAME_OPTION)
	{
		clearScreen();
		exitMenu = true;
	}
	else if (MENU_OPTIONS[arrowId] == EXIT_OPTION)
	{
		clearScreen();
		exitFlag = true;
		exitMenu = true;
	}

	return exitMenu;
}

bool Menu::displayMainMenu()
{
	gotoMainScreen();
	Sleep(LINE_PRINT_DELAY*3);
	
	update();
	
	return exitFlag;
}
