#include "Menu.h"

void Menu::print(const char* screen[HEIGHT]) const
{
	for (int i = 0; i < HEIGHT - 1; i++) {
		std::cout << screen[i] << '\n';
		Sleep(70);
	}
	Sleep(70);
	std::cout << screen[HEIGHT - 1];
}

void Menu::update()
{
	while(true)
	{
		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();
				if(std::tolower(key) == KEYS[UP])
				{
					//erase arrow from prev position 
					draw(' ', MENU_OPTIONS[arrowId].screenPosition);
					arrowId = (arrowId - 1 + NUM_OF_OPTIONS) % NUM_OF_OPTIONS;
				}
				if(std::tolower(key) == KEYS[DOWN])
				{
					draw(' ', MENU_OPTIONS[arrowId].screenPosition);
					arrowId = (arrowId + 1) % NUM_OF_OPTIONS;
				}
				//ENTER
				if(key == KEYS[SELECT])
				{
					//do something
					break;
				}
			}
			
			draw(ARROW, MENU_OPTIONS[arrowId].screenPosition);
			
			Sleep(65);
		}
	}
}

void Menu::start()
{
	displayMainScreen();
	Sleep(300);
	
	update();
}
