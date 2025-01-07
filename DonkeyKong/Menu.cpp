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

void Menu::updateArrowByKey(char key)
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
	int optionCounter = 0;
	for (const auto& filename : levelFileNames)
	{
		Point optionPos = { 0, optionCounter };
		optionPos = optionPos + LEVEL_OPTIONS_POS;
		char hotkey = '0' + optionCounter;
		// create menu options for all the levels 
		MenuOption option = {optionPos, filename.c_str(), hotkey};
		levelOptions.push_back(option);
		optionCounter++;
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
	//  saved in the buffer that khbit uses, this function cleans the buffer after the animation
	flushInputBuffer();
}

void Menu::printLevelOptions() const
{
	int startId = scrollValue * MAX_LEVELS_ON_SCREEN;
	int stopId = startId + MAX_LEVELS_ON_SCREEN;
	// check that stopId is in bounds of the vector
	if(stopId > levelFileNames.size() - 1)
	{
		stopId = levelFileNames.size();
	}
	                               // +1 for [Back] option
	for (int i = startId; i < stopId + 1; i++)
	{
		auto option = levelOptions[i];
		gotoScreenPos(option.screenPosition);
		std::cout << ' ' << option.hotkey << '.';
		std::cout << option.text;
	}

	// during this animation we dont register input but it is still 
	//  saved in the buffer that khbit uses, this function cleans the buffer after the animation
	flushInputBuffer();
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
			
			if(currentScreenId == MAIN_SCREEN_ID || currentScreenId == LEVELS_SCREEN_ID)
			{
				// try to update arrow with this key 
				updateArrowByKey(key);

				//try to select option with this key
				closeMenu = selectOption(key);
			}

			//user pressed ENTER
			if(key == KEYS[SELECT])
			{
				closeMenu = selectOption();
			}

			if(closeMenu) 
			{
				break; //user selected one of the option that closes the menu
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
		return closeMenu;
	}

	if(currentScreenId == LEVELS_SCREEN_ID)
	{
		// back option
		if(arrowId == currNumOfOptions-1)
		{
			clearScreen();
			gotoMainScreen();
			return closeMenu;
		}
		else
		{
			clearScreen();
			chosenLevelId = arrowId;
			closeMenu = true;
			return closeMenu;
		}
	}

	if (currentScreenId == GAMEOVER_SCREEN_ID || currentScreenId == WIN_SCREEN_ID)
	{
		clearScreen();
		// game over and win screen do break the input loop
		closeMenu = true;
		return closeMenu;
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

bool Menu::selectOption(char hotkey)
{
	bool closeMenu = false;
	// this function only works on the main screen
	if(currentScreenId == MAIN_SCREEN_ID)
	{
		if (hotkey == CONTROLS_OPTION.hotkey)
		{
			clearScreen();
			gotoControlScreen();
		}
		else if (hotkey == LEVELS_OPTION.hotkey)
		{
			clearScreen();
			gotoLevelsScreen();
		}
		else if (hotkey == START_GAME_OPTION.hotkey)
		{
			clearScreen();
			closeMenu = true;
		}
		else if (hotkey == EXIT_OPTION.hotkey)
		{
			clearScreen();
			exitFlag = true;
			closeMenu = true;
		}
	}

	else if (currentScreenId == LEVELS_SCREEN_ID)
	{
		for (const auto& option : levelOptions)
		{
			if (hotkey == EXIT_OPTION.hotkey)
			{
				clearScreen();
				gotoMainScreen();
				return closeMenu;
			}
			else if(option.hotkey == hotkey)
			{
				clearScreen();
				chosenLevelId = arrowId;
				closeMenu = true;
				return closeMenu;
			}
		}
	}

	return closeMenu;
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
	currNumOfOptions = levelFileNames.size() + 1;
	print(levelsScreen, LINE_PRINT_DELAY);
	setLevelOptionPositions();
	printLevelOptions();
	currentScreenId = LEVELS_SCREEN_ID;
}

bool Menu::displayMainMenu()
{
	gotoMainScreen();
	Sleep(LINE_PRINT_DELAY);
	
	update();
	
	return exitFlag;
}
