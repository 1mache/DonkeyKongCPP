#include "Menu.h"

void Menu::drawArrow()
{
	if(currentScreenId == MAIN_SCREEN_ID)
	{
		drawChar(ARROW, MAINMENU_OPTIONS[arrowId].screenPosition);
	}
	else if(currentScreenId == LEVELS_SCREEN_ID)
	{
		drawChar(ARROW, levelOptions[arrowId].screenPosition);
	}
}

void Menu::eraseArrow()
{
	if(currentScreenId == MAIN_SCREEN_ID)
	{
		eraseChar(MAINMENU_OPTIONS[arrowId].screenPosition);
	}
	else
	{
		eraseChar(levelOptions[arrowId].screenPosition);
	}
}

void Menu::tryUpdateArrow(char key)
{
	//check if its arrow contol key
	if (std::tolower(key) == KEYS[UP])
	{
		//erase arrow from prev position 
		eraseArrow();
		arrowId = (arrowId - 1 + currNumOfOptions) % currNumOfOptions;
	}
	else if (std::tolower(key) == KEYS[DOWN])
	{
		eraseArrow();
		arrowId = (arrowId + 1) % currNumOfOptions;
	}
}

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
	
	// during this animation we dont register input but it is still 
	//  saved in the buffer that khbit uses, this function cleans the buffer after the animation
	flushInputBuffer();
}

void Menu::setLevelOptionPositions()
{
	levelOptions.clear();

	int startId = scrollValue * MAX_LEVELS_ON_SCREEN;
	int stopId = startId + MAX_LEVELS_ON_SCREEN;
	// check that stopId is in bounds of the vector
	if (levelFileNames.size() == 0 || stopId > levelFileNames.size() - 1)
	{
		stopId = levelFileNames.size();
	}

	int optionOffset = 0;
	for (int i = startId; i < stopId; i++)
	{
		const auto& filename = levelFileNames[i];
		optionOffset = i - startId;
		Point optionPos = LEVEL_OPTIONS_POS + Point(0, optionOffset);
		char hotkey = '0' + optionOffset;

		// create menu options for all the levels 
		MenuOption option = { optionPos, filename.c_str(), hotkey };
		levelOptions.push_back(option);
	}
	// create another option that is the exit option
	MenuOption backOption = { EXIT_OPTION.screenPosition, "[BACK]", EXIT_OPTION.hotkey };
	levelOptions.push_back(backOption);
}

void Menu::printMainOptions() const
{
	for(const MenuOption& option: MAINMENU_OPTIONS)
	{
		gotoScreenPos(option.screenPosition);
		int textLen = strlen(option.text);
		std::cout << " (" << option.hotkey << ')';

		for (int i = 0; i < textLen; i++)
		{
			std::cout << option.text[i];
			Sleep(LINE_PRINT_DELAY);
		}
	}

	// during this animation we dont register input but it is still 
	// saved in the buffer that khbit uses, this function cleans the buffer after the animation
	flushInputBuffer();
}

void Menu::printLevelOptions() const
{
	for (const auto& option : levelOptions)
	{
		gotoScreenPos(option.screenPosition);
		std::cout << " (" << option.hotkey << ')';
		std::cout << option.text;
	}
}

void Menu::update()
{
	// breaks out of the menu loop
	bool closeMenu = false;
	
	while (true)
	{
		if (_kbhit())
		{
			char key = _getch();

			//try to select option with this key
			closeMenu = selectOption(key);

			if(closeMenu) 
			{
				break; //user selected one of the option that closes the menu
			}
			
			if(currentScreenId == MAIN_SCREEN_ID)
			{
				// try to update arrow with this key 
				tryUpdateArrow(key);
			}
			if(currentScreenId == LEVELS_SCREEN_ID)
			{
				// try to scroll with this key
				tryScroll(key);
				// try to update arrow with this key 
				tryUpdateArrow(key);
			}
		}

		//draw arrow if were on a screen that has arrow main screen 
		drawArrow();

		Sleep(Constants::GAME_REFRESH_RATE);
	}
}

bool Menu::selectOption()
{
	bool closeMenu = false;

	//if were on the control screen there is always a single option
	if (currentScreenId == CONTROL_SCREEN_ID)
	{
		clearScreen();
		gotoMainScreen();
		// control screen doesnt break the input loop
		return false;
	}

	if(currentScreenId == LEVELS_SCREEN_ID)
	{
		// back option
		if(arrowId == currNumOfOptions-1)
		{
			clearScreen();
			gotoMainScreen();
			return false;
		}
		else
		{
			clearScreen();
			chosenLevelId = arrowId + (scrollValue * MAX_LEVELS_ON_SCREEN);
			// we chose level so the menu closes
			return true;
		}
	}

	if (currentScreenId == GAMEOVER_SCREEN_ID || currentScreenId == WIN_SCREEN_ID)
	{
		clearScreen();
		// game over and win screen do break the input loop, one cycle of the game ensded
		return true;
	}
	//if were on the main screen there is a bunch of options and the arrow tells us what we selected
	if (MAINMENU_OPTIONS[arrowId] == CONTROLS_OPTION)
	{
		clearScreen();
		gotoControlScreen();
	}
	else if (MAINMENU_OPTIONS[arrowId] == LEVELS_OPTION)
	{
		clearScreen();
		gotoLevelsScreen();
	}
	else if (MAINMENU_OPTIONS[arrowId] == START_GAME_OPTION)
	{
		clearScreen();
		closeMenu = true;
	}
	else if (MAINMENU_OPTIONS[arrowId] == EXIT_OPTION)
	{
		clearScreen();
		exitFlag = true;
		closeMenu = true;
	}

	return closeMenu;
}

bool Menu::selectOption(char key)
{
	// we have separate function for processing selection with ENTER
	if(key == KEYS[SELECT])
	{
		return selectOption();
	}

	bool closeMenu = false;
	if(currentScreenId == MAIN_SCREEN_ID)
	{
		if (key == CONTROLS_OPTION.hotkey)
		{
			clearScreen();
			gotoControlScreen();
		}
		else if (key == LEVELS_OPTION.hotkey)
		{
			clearScreen();
			gotoLevelsScreen();
		}
		else if (key == START_GAME_OPTION.hotkey)
		{
			clearScreen();
			closeMenu = true;
		}
		else if (key == EXIT_OPTION.hotkey)
		{
			clearScreen();
			exitFlag = true;
			closeMenu = true;
		}
	}

	else if (currentScreenId == LEVELS_SCREEN_ID)
	{
		if (key == EXIT_OPTION.hotkey)
		{
			clearScreen();
			gotoMainScreen();
			return closeMenu;
		}

		// try to find the match for a hotkey among the level options 
		for (const auto& option : levelOptions)
		{
			if(option.hotkey == key)
			{
				clearScreen();
				// number representation of our hotkey ( hotkey is a digit )
				int hotkeyNum = key - '0';
				chosenLevelId = hotkeyNum + (scrollValue * MAX_LEVELS_ON_SCREEN);
				closeMenu = true;
				return closeMenu;
			}
		}
	}

	return closeMenu;
}

void Menu::tryScroll(char key)
{
	//if the key is right and if we have more than 9 levels
	if(key == KEYS[SCROLL] && maxScrolls > 1)
	{
		scrollValue = (scrollValue + 1) % maxScrolls;
		clearScreen();
		levelOptions.clear();

		// launch the screen again, this time the next set of options will be shown
		gotoLevelsScreen();
	}
}

void Menu::gotoMainScreen()
{
	arrowId = START_ARROW_ID;
	currNumOfOptions = NUM_OF_MAIN_OPTIONS;
	print(mainScreen, LINE_PRINT_DELAY);
	printMainOptions();
	currentScreenId = MAIN_SCREEN_ID;
}

void Menu::gotoLevelsScreen()
{
	arrowId = START_ARROW_ID;
	// all the levels + "back to main menu" option
	print(levelsScreen, LINE_PRINT_DELAY);
	setLevelOptionPositions();
	currNumOfOptions = levelOptions.size();
	printLevelOptions();

	// if there are levels that didnt fit in one screen display hint on how to scroll 
	if(maxScrolls > 1)
	{
		gotoScreenPos(SCROLL_HINT_POS);
		std::cout << SCROLL_HINT_MESSAGE;
	}

	currentScreenId = LEVELS_SCREEN_ID;
}

bool Menu::displayMainMenu()
{
	gotoMainScreen();
	Sleep(LINE_PRINT_DELAY);
	
	update();
	
	return exitFlag;
}

void Menu::displayWinScreen(int finalScore)
{
	gotoWinScreen();

	gotoScreenPos(WIN_SCORE_POS);
	std::cout << "Score: " << finalScore;

	update();
}
