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
		char hotkey;

		bool operator==(const MenuOption& other) const
		{
			return hotkey == other.hotkey;
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
	static constexpr MenuOption START_GAME_OPTION = { Point(31, 18), " [1] Start Game", '1'};
	static constexpr MenuOption CONTROLS_OPTION = { Point(32, 19), " [8] Controls", '8' };
	static constexpr MenuOption EXIT_OPTION = { Point(34, 21), " [9] EXIT", '9'};

	static constexpr MenuOption MENU_OPTIONS[NUM_OF_OPTIONS] = { START_GAME_OPTION, CONTROLS_OPTION, EXIT_OPTION };

	static constexpr const char* mainScreen[HEIGHT] = {
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
			"Q    X/W   - navigate                                                          Q", // 18
			"Q            options                                                           Q", // 19
			"Q                                                                              Q", // 20
			"Q    ENTER - select                                                            Q", // 21
			"Q                                                                              Q", // 22
			"Q                                                                              Q", // 23
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 24
	};

	static constexpr const char* controlScreen[HEIGHT] = {
		//   00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
			"Q                                                                              Q", // 1
			"Q                                                                              Q", // 2
			"Q   CCCCC   OOOOO   N   N  TTTTT  RRRR    OOOOO   L      SSSSS   w*W*W*W*w     Q", // 3
			"Q  C       O     O  NN  N    T    R   R  O     O  L      S        \\\".\".\"/      Q", // 4
			"Q  C       O     O  N N N    T    RRRR   O     O  L       SSS      //`\\\\       Q", // 5
			"Q  C       O     O  N  NN    T    R   R  O     O  L          S    (/a a\\)      Q", // 6
			"Q   CCCCC   OOOOO   N   N    T    R   R   OOOOO   LLLLL  SSSSS    (\\_-_/)      Q", // 7
			"Q                                                                .-~'='~-.     Q", // 8
			"Q                                                               /`~`\"Y\"`~`\\    Q", // 9
			"Q                                                              / /(  *  )\\ \\   Q", // 10
			"Q                  $                                          / /  )   (  \\ \\  Q", // 11
			"Q       =>>>>>>>>>>>>>>=                                      \\ \\_/\\\\_//\\_/ /  Q", // 12
			"Q       H              H                                       \\/_) '*' (_\\/   Q", // 13
			"Q       H      @       H                                         |       |     Q", // 14
			"Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=     =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 15
			"Q                                                                              Q", // 16
			"Q                                                                              Q", // 17
			"Q             A - Move Left | D - Move Right | W - Jump/Climb Up               Q", // 18
			"Q                             X - Climb Down | ESC - Pause                     Q", // 19
			"Q                                                                              Q", // 20
			"Q                                                                              Q", // 21
			"Q                                   > Back                                     Q", // 22
			"Q                                                                              Q", // 23
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 24
	};

	static constexpr const char* gameOverScreen[HEIGHT] = {
		// 00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q       GGG    AAAAA   M   M   EEEEE       OOO    V     V   EEEEE   RRRR       Q", // 2
		  "Q      G       A   A   MM MM   E          O   O    V   V    E       R   R      Q", // 3
		  "Q      G  GG   AAAAA   M M M   EEEE       O   O     V V     EEEE    RRRR       Q", // 4
		  "Q      G   G   A   A   M   M   E          O   O      V      E       R  R       Q", // 5
		  "Q       GGG    A   A   M   M   EEEEE       OOO       V      EEEEE   R   R      Q", // 6
		  "Q                                                                              Q", // 7
		  "Q                            ,-'~~~\\         __                                Q", // 8
		  "Q                          ,'        ~____/~~~%%',                             Q", // 9
		  "Q                         (                    %  Y                            Q", // 10
		  "Q                        {                      %% I                           Q", // 11
		  "Q                       {      -                 %  `.                         Q", // 12
		  "Q                       |       ',                %  )                         Q", // 13
		  "Q                       |        |   ,..__      __. Y                          Q", // 14
		  "Q                       |    .,_./  Y ' / ^Y   J   )|                          Q", // 15
		  "Q                       \\           |' /   |   |   ||                          Q", // 16
		  "Q                        \\          L_/    . _ (_,.'(                          Q", // 17
		  "Q                         \\,   ,      ^^\"\"' / |      )                         Q", // 18
		  "Q                           \\_  \\          /,L]     /                          Q", // 19
		  "Q      Press ENTER             '-_`-,       ` `   ./`        to try again.     Q", // 20
		  "Q                                 `-(_            )                            Q", // 21
		  "Q                                     ^^\\..___,.--`                            Q", // 22
		  "Q                                                                              Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
		  
	};

	static constexpr const char* winScreen[HEIGHT] = {
		// 00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                                                              Q", // 1
		  "Q            Y   Y   OOO    U   U       W     W    OOO    N   N    #           Q", // 2
		  "Q             Y Y   O   O   U   U       W     W   O   O   NN  N    #           Q", // 3
		  "Q              Y    O   O   U   U       W  W  W   O   O   N N N    #           Q", // 4
		  "Q              Y    O   O   U   U       W  W  W   O   O   N  NN                Q", // 5
		  "Q              Y     OOO     UUU          W W      OOO    N   N    0           Q", // 6
		  "Q                                                                              Q", // 7
		  "Q                          Press ENTER to play again.                          Q", // 8
		  "Q                                                                              Q", // 9
		  "Q                                                     w*W*W*W*w                Q", // 10
		  "Q                                      _  _            \\\".\".\"/                 Q", // 11
		  "Q                 _________           ( \\/ )            //`\\\\                  Q", // 12
		  "Q                (____M____)           \\  /            (/a a\\)                 Q", // 13
		  "Q                 \\_______/             \\/             (\\_-_/)                 Q", // 14
		  "Q                 #|a`_`a|#                           .-~'='~-.                Q", // 15
		  "Q                  \\ %%% /                           /`~`\"Y\"`~`\\               Q", // 16
		  "Q                  |\\___/|                          / /(  *  )\\ \\              Q", // 17
		  "Q         ___ ____/:     :\\____ ___                / /  )   (  \\ \\             Q", // 18
		  "Q       .'   `.-===-\\   /-===-.`   '.              \\ \\_/\\\\_//\\_/ /             Q", // 19
		  "Q      /    .-\"\"\"\"\" - . - \"\"\"\"\"-.    \\              \\/_) '*' (_\\/              Q", // 20
		  "Q     /'             =:=             '\\               |       |                Q", // 21
		  "Q   .'  ' .:        -=:=-        :. '  `.             |       |                Q", // 22
		  "Q   (.'   /'. '-.....-'-.....-' .'\\   '.)             |       |                Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	static constexpr int MAIN_SCREEN_ID = 0;
	static constexpr int CONTROL_SCREEN_ID = 1;
	static constexpr int WIN_SCREEN_ID = 2;
	static constexpr int GAMEOVER_SCREEN_ID = 3;

	//which screen are we on
	int currentScreenId = MAIN_SCREEN_ID;
	//what menu option the arrow is pointing to
	int arrowId = START_ARROW_ID;
	bool exitFlag = false;

	void drawChar(char ch, Point position) const
	{
		gotoScreenPos(position);
		std::cout << ch;
	}

	void eraseChar(Point position) const
	{
		drawChar(' ', position);
	}

	void print(const char* const screen[HEIGHT], int lineSleep) const;
	void printMainOptions();

	void update();
	bool selectOption();
	//overloading for selecting options with numbers
	bool selectOption(char hotkey);

	void gotoMainScreen();

	void gotoControlScreen()
	{
		print(controlScreen, LINE_PRINT_DELAY);
		currentScreenId = CONTROL_SCREEN_ID;
	}

	void gotoGameOverScreen()
	{
		print(gameOverScreen, LINE_PRINT_DELAY * 2);
		currentScreenId = GAMEOVER_SCREEN_ID;
	}

	void gotoWinScreen()
	{
		print(winScreen, LINE_PRINT_DELAY * 2);
		currentScreenId = WIN_SCREEN_ID;
	}

public:
	bool displayMainMenu();
	void displayGameOver() 
	{
		gotoGameOverScreen();
		update();
	}
	void displayWinScreen()
	{
		gotoWinScreen();
		update();
	}
};