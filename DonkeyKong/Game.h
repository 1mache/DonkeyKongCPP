#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>

#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "Menu.h"
#include "Barrel.h"
#include "BarrelManager.h"

using std::ifstream;

class Game
{
	static constexpr int ESC = 27;
	static constexpr Point POS_NOT_SET = {-1 , -1};
	static constexpr char MARIO_SPRITE = '@';
	static constexpr Point PAUSEMESSAGE_POS = { 4 , 2 };
	static constexpr Point LIVES_COUNTER_POS = { 74, 3 };
	static constexpr const char* SCREEN_FILE_NAME = "dkong_*.screen";
	static constexpr int NUM_OF_LEVELS = 3;
	static constexpr const char* PAUSE_MESSAGE = "Paused | ESC to continue";
	static constexpr int MAX_LIVES = 3;

	//will be set when we read from file
	Point marioStartPos = POS_NOT_SET;
	Point donkeyKongPos = POS_NOT_SET;
	Point paulinePos = POS_NOT_SET;

	Board* gameBoard = nullptr;
	Player* player = nullptr;

	BarrelManager* barrelManager = nullptr;

	int lives = MAX_LIVES;

	bool isPaused = false;

	// game loop
	void update();

	// what happens when mario gets hurt
	bool handleStrike();

	// update the lives counter on screen
	void updateLivesCounter() const
	{
		gotoScreenPos(LIVES_COUNTER_POS);
		std::cout << lives;
	}

	void pauseGame();

	void continueGame();

	//reads all the necessary info from level file, returns true if was successful 
	bool readLevelFromFile();

public:
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game()
	{
		delete gameBoard;
		delete player;
		delete barrelManager;
	}
	
	bool start();

	void resetLevel();
};