#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "Menu.h"
#include "Barrel.h"
#include "BarrelManager.h"

class Game
{
	static constexpr int ESC = 27;
	static constexpr char MARIO_SPRITE = '@';
	static constexpr Point MARIO_START_POS = { 2, 23 };
	static constexpr Point DONKEY_KONG_POS = { 39, 3 };
	static constexpr Point PAUSEMESSAGE_POS = { 4 , 2 };
	static constexpr Point PAULINE_POS = { 39, 1 };
	static constexpr Point LIVES_COUNTER_POS = { 74, 3 };
	static constexpr const char* SCREEN_FILE_NAME = "dkong_*.screen";
	static constexpr int NUM_OF_LEVELS = 3;
	static constexpr const char* PAUSE_MESSAGE = "Paused | ESC to continue";
	static constexpr int MAX_LIVES = 3;

	Board gameBoard;
	Player player;

	BarrelManager barrelManager;

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
	Game(): player(Player(&gameBoard, MARIO_SPRITE, MARIO_START_POS)), 
		barrelManager(BarrelManager(&gameBoard, DONKEY_KONG_POS)) {}
	
	bool start();

	void resetLevel();
};