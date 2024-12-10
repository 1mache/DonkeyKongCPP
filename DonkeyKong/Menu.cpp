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
	
	while (true)
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

			//ENTER
			if(key == KEYS[SELECT])
			{
				if(currentScreenId == CONTROL_SCREEN_ID)
				{
					clearScreen();
					displayMainScreen();
				}
				else
				{
					if (MENU_OPTIONS[arrowId] == CONTROLS_OPTION)
					{
						clearScreen();
						gotoxy(0, 0);
						displayControls();
					}
					else if(MENU_OPTIONS[arrowId] == START_GAME_OPTION)
					{
						clearScreen();
						break;
					}
				}
			}
		}

		if(currentScreenId == MAIN_SCREEN_ID)
		{
			drawChar(ARROW, MENU_OPTIONS[arrowId].screenPosition);
		}
			
		Sleep(65);
	}
}

void Menu::start()
{
	displayMainScreen();
	Sleep(LINE_PRINT_DELAY*3);
	
	update();
}
