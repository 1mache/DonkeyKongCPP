#pragma once
#include <cstring>
#include <iostream>
#include <conio.h>
#include <windows.h>

#include "Point.h"
#include "Constants.h"
#include "utils.h"

class Menu
{
	struct MenuOption
	{
		Point screenPosition;
		const char* text;

		bool operator==(const MenuOption& other) const
		{
			return screenPosition == other.screenPosition;
		}
	};

	static constexpr int WIDTH = Constants::SCREEN_WIDTH;
	static constexpr int HEIGHT = Constants::SCREEN_HEIGHT;
	static constexpr char ARROW = '>';
	static constexpr int START_ARROW_ID = 0;
	static constexpr int LINE_PRINT_DELAY = 30;

	enum INPUTS { UP, DOWN, SELECT };
	static constexpr char KEYS[] = { 'w', 'x', '\r' };
	static constexpr int NUM_OF_OPTIONS = 3;
	static constexpr MenuOption START_GAME_OPTION = { Point(32, 18), " Start Game" };
	static constexpr MenuOption CONTROLS_OPTION = { Point(32, 19), "  Controls" };
	static constexpr MenuOption EXIT_OPTION = { Point(32, 21), "   EXIT" };

	static constexpr MenuOption MENU_OPTIONS[NUM_OF_OPTIONS] = { START_GAME_OPTION, CONTROLS_OPTION, EXIT_OPTION };
	
	const char* mainScreen[HEIGHT] = {
		//   00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
			"Q                                                                              Q", // 1
			"Q                                                                              Q", // 2
			"Q        DDDDD     OOOOO    N   N   K   K   EEEEE   Y   Y       .\"`\".          Q", // 3
			"Q        D    D   O     O   NN  N   K  K    E        Y Y    .-./ _=_ \\.-.      Q", // 4
			"Q        D    D   O     O   N N N   KKK     EEEE      Y    {  (,(oYo),) }}     Q", // 5
			"Q        D    D   O     O   N  NN   K  K    E         Y   { { |   \"   | } }    Q", // 6
			"Q        DDDDD     OOOOO    N   N   K   K   EEEEE     Y   {  { \\(---)/ }  }    Q", // 7
			"Q                                                          {{  }'-=-'{ } }     Q", // 8
			"Q        K   K   OOOOO    N   N   GGGG                     { { }._:_.{ } }     Q", // 9
			"Q        K  K   O     O   NN  N   G                        {{  } -:- { } }     Q", // 10
			"Q        KKK    O     O   N N N   G  GG                    {_{ }`===`{  _}     Q", // 11
			"Q        K  K   O     O   N  NN   G   G                   ((((\\)     (/))))    Q", // 12
			"Q        K   K   OOOOO    N   N   GGGG                                         Q", // 13
			"Q                                                                              Q", // 14
			"Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=     =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 15
			"Q                                                                              Q", // 16
			"Q                                                                              Q", // 17
			"Q                                 Start Game                                   Q", // 18
			"Q                                  Controls                                    Q", // 19
			"Q                                                                              Q", // 20
			"Q                                    EXIT                                      Q", // 21
			"Q                                                                              Q", // 22
			"Q                                                     by: B&D Entertaiment     Q", // 23
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 24
	};

	const char* controlScreen[HEIGHT] = {
		//   00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
			"Q                                                                              Q", // 1
			"Q                                                                              Q", // 2
			"Q        DDDDD     OOOOO    N   N   K   K   EEEEE   Y   Y                      Q", // 3
			"Q        D    D   O     O   NN  N   K  K    E        Y Y                       Q", // 4
			"Q        D    D   O     O   N N N   KKK     EEEE      Y                        Q", // 5
			"Q        D    D   O     O   N  NN   K  K    E         Y                        Q", // 6
			"Q        DDDDD     OOOOO    N   N   K   K   EEEEE     Y                        Q", // 7
			"Q                                                                              Q", // 8
			"Q        K   K   OOOOO    N   N   GGGG                                         Q", // 9
			"Q        K  K   O     O   NN  N   G                                            Q", // 10
			"Q        KKK    O     O   N N N   G  GG                                        Q", // 11
			"Q        K  K   O     O   N  NN   G   G                                        Q", // 12
			"Q        K   K   OOOOO    N   N   GGGG              by: B&D Entertaiment       Q", // 13
			"Q                                                                              Q", // 14
			"Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=     =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 15
			"Q                                                                              Q", // 16
			"Q                                  Controls:                                   Q", // 17
			"Q                                                                              Q", // 18
			"Q             A - Move Left | D - Move Right | W - Jump/Climb Up               Q", // 19
			"Q                             X - Climb Down                                   Q", // 20
			"Q                                                                              Q", // 21
			"Q                                   > Back                                     Q", // 22
			"Q                                                                              Q", // 23
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 24
	};
	
	static constexpr int MAIN_SCREEN_ID = 0;
	static constexpr int CONTROL_SCREEN_ID = 1;
	
	//which screen are we on
	int currentScreenId = MAIN_SCREEN_ID; 
	//what menu option the arrow is pointing to
	int arrowId = START_ARROW_ID;

	void drawChar(char ch, Point position) const
	{
		gotoxy(position.getX(), position.getY());
		std::cout << ch;
	}

	void eraseChar(Point position) const
	{
		drawChar(' ', position);
	}

	void print(const char* const screen[HEIGHT], int lineSleep) const;

	void clearScreen() 
	{
		//empties the console screen
		system("cls");
	}

	void update();
	
	void displayMainScreen() 
	{
		arrowId = START_ARROW_ID;
		print(mainScreen, LINE_PRINT_DELAY);
		currentScreenId = MAIN_SCREEN_ID;

	}

	void displayControls()
	{
		print(controlScreen, LINE_PRINT_DELAY);
		currentScreenId = CONTROL_SCREEN_ID;
	}

public:
	void start();

};