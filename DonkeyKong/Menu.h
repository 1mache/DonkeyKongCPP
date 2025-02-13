#pragma once
#include <cstring>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>

#include "Point.h"
#include "GameOptions.h"
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

	static constexpr int WIDTH = GameOptions::SCREEN_WIDTH;
	static constexpr int HEIGHT = GameOptions::SCREEN_HEIGHT;
	static constexpr char ARROW = '>';
	static constexpr int START_ARROW_ID = 0;
	static constexpr int LINE_PRINT_DELAY = 30;

	enum INPUTS { UP, DOWN, SELECT, SCROLL };
	static constexpr char KEYS[] = { 'w', 'x', '\r', ' '};
	static constexpr int NUM_OF_MAIN_OPTIONS = 4;
	static constexpr MenuOption START_GAME_OPTION = { Point(31, 18), "[Start Game]", '1'};
	static constexpr MenuOption CONTROLS_OPTION = { Point(32, 19), "[Controls]", '7' };
	static constexpr MenuOption LEVELS_OPTION = { Point(33, 20), "[Levels]", '8' };
	static constexpr MenuOption EXIT_OPTION = { Point(34, 21), "[EXIT]", '9'};
	static constexpr Point WIN_SCORE_POS = { 6, 11 };

	static constexpr MenuOption MAINMENU_OPTIONS[NUM_OF_MAIN_OPTIONS] = { START_GAME_OPTION, CONTROLS_OPTION, LEVELS_OPTION, EXIT_OPTION };

	static constexpr int MAX_LEVELS_ON_SCREEN = 9;
	static constexpr Point LEVEL_OPTIONS_POS = { 30, 4 };
	static constexpr Point SCROLL_HINT_POS = { 4, 16 };
	static constexpr const char* SCROLL_HINT_MESSAGE = "SPACE - SCROLL FOR MORE LEVELS";

	static constexpr const char* mainScreen[HEIGHT] = {
		//   00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
			"Q                                                                              Q", // 1
			"Q      DDDDD     OOOOO    N   N   K   K   EEEEE   Y   Y         .\"`\".          Q", // 2
			"Q      D    D   O     O   NN  N   K  K    E        Y Y      .-./ _=_ \\.-.      Q", // 3
			"Q      D    D   O     O   N N N   KKK     EEEE      Y      {  (,(oYo),) }}     Q", // 4
			"Q      D    D   O     O   N  NN   K  K    E         Y     { { |   \"   | } }    Q", // 5
			"Q      DDDDD     OOOOO    N   N   K   K   EEEEE     Y     {  { \\(---)/ }  }    Q", // 6
			"Q                                                          {{  }'-=-'{ } }     Q", // 7
			"Q      K   K   OOOOO    N   N   GGGG                       { { }._:_.{ } }     Q", // 8
			"Q      K  K   O     O   NN  N   G                          {{  } -:- { } }     Q", // 9
			"Q      KKK    O     O   N N N   G  GG                      {_{ }`===`{  _}     Q", // 10
			"Q      K  K   O     O   N  NN   G   G                     ((((\\)     (/))))    Q", // 11
			"Q      K   K   OOOOO    N   N   GGGG                                           Q", // 12
			"Q                                                                              Q", // 13
			"Q                                        by Ben Liberman and Dmytro Kreicherek Q", // 14
			"Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=         =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 15
			"Q                                                                              Q", // 16
			"Q                                                                              Q", // 17
			"Q   X/W   - navigate                                                           Q", // 18
			"Q           options                                                            Q", // 19
			"Q   ENTER - select                                                             Q", // 20
			"Q                                                                              Q", // 21
			"Q   (or use 1,7,8,9)                                                           Q", // 22
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
			"Q             X - Climb Down | ESC - Pause   | P - Use Hammer                  Q", // 19
			"Q                                                                              Q", // 20
			"Q                                                                              Q", // 21
			"Q                                ENTER - Back                                  Q", // 22
			"Q                                                                              Q", // 23
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 24
	};

	static constexpr const char* levelsScreen[HEIGHT] = {
		//   00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
			"Q                                                                              Q", // 1
			"Q                                     LEVELS:                                  Q", // 2
			"Q                                                                              Q", // 3
			"Q                                                                              Q", // 4
			"Q                                                                              Q", // 5
			"Q                                                                              Q", // 6
			"Q                                                                              Q", // 7
			"Q                                                                              Q", // 8
			"Q                                                                              Q", // 9
			"Q                                                                              Q", // 10
			"Q                                                                              Q", // 11
			"Q                                                                              Q", // 12
			"Q                                                                              Q", // 13
			"Q                                                                              Q", // 14
			"Q                                                                              Q", // 15
			"Q                                                                              Q", // 16
			"Q                                                                              Q", // 17
			"Q   X/W   - navigate                                                           Q", // 18
			"Q           options                                                            Q", // 19
			"Q   ENTER - select                                                             Q", // 20
			"Q                                                                              Q", // 21
			"Q                                                                              Q", // 22
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

	//each screen has an ID 
	static constexpr int MAIN_SCREEN_ID = 0;
	static constexpr int CONTROL_SCREEN_ID = 1;
	static constexpr int LEVELS_SCREEN_ID = 2;
	static constexpr int WIN_SCREEN_ID = 3;
	static constexpr int GAMEOVER_SCREEN_ID = 4;

	//which screen are we on
	int currentScreenId = MAIN_SCREEN_ID;

	//what menu option the arrow is pointing to
	int arrowId = START_ARROW_ID;
	// how many options we currently have on screen
	int currNumOfOptions = NUM_OF_MAIN_OPTIONS;
	// if there are too many levels to show at once we show them in groups of 9
	int scrollValue = 0;

	// tells us if we selected the exit option
	bool exitFlag = false;
	
	// by default the user "chooses" to play from the first level by selecting start game
	int chosenLevelId = 0;
	//level file names that we will display on separate screen
	const std::vector<std::string>& levelFileNames;
	// all the options to choose from on the levels screen
	std::vector<MenuOption> levelOptions;
	// amount of times we can scroll before we get to the first 9 levels again
	const int maxScrolls;

	void drawChar(char ch, Point position) const
	{
		DK_utils::drawSymbolOnScreen(ch, position);
	}

	void eraseChar(Point position) const
	{
		DK_utils::drawSymbolOnScreen(' ', position);
	}

	void drawArrow();
	void eraseArrow();

	// if the key given to the function is relevant, updates arrow position on screen(if this screen has arrow)
	void tryUpdateArrow(char key);

	// prints the given screen
	void print(const char* const screen[HEIGHT], int lineSleep) const;

	// builds the leveOptions vector
	void setLevelOptionPositions();
	// print the menu options with sleep between characters (animation)
	void printMainOptions() const;
	// prints all the levels to choose from on the levels screen
	void printLevelOptions() const;

	// updates menu based on input 
	void update();

	// selecting options with ENTER, returns whether the Menu closes after we selected something
	// for example "start game" closes the menu because the game starts 
	bool selectOption();
	
	//overloading for selecting options with numbers
	bool selectOption(char hotkey);

	// relevant only to the levels screen
	// if the key given to us is the scroll key this will show the next batch of options
	void tryScroll(char key);

	void gotoMainScreen();

	void gotoLevelsScreen();

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
	Menu(const std::vector<std::string>& _levelFileNames): levelFileNames(_levelFileNames),
		maxScrolls((_levelFileNames.size() / MAX_LEVELS_ON_SCREEN) + 1) {}

	// returns true if we selected EXIT in menu 
	bool displayMainMenu();

	void displayGameOver()
	{
		gotoGameOverScreen();
		update();
	}

	void displayWinScreen(int finalScore);

	int getChosenLevelId() const
	{
		return chosenLevelId;
	}
};