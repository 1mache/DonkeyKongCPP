#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "Menu.h"
#include "Barrel.h"
#include "DonkeyKong.h"

class Game
{
	static constexpr int ESC = 27;
	static constexpr char MARIO_SPRITE = '@';
	static constexpr char DONKEY_KONG_SPRITE = 'O';
	static constexpr Point MARIO_START_POS = { 2, 23 };
	static constexpr Point DONKEY_KONG_POS = { 13, 3 };
	static constexpr Point PAUSEMESSAGE_POS = { 31, 2 };
	// ChatGPT said that this is the way for static constexpr string
	static constexpr const char* PAUSE_MESSAGE = "Game Paused: Press ESC to continue";

	int barrelsDelayAmount = 2;
	int delayCounter = 0;

	Board gameBoard;
	Player player;

	DonkeyKong dk;

	bool isPaused = false;
	bool gameOver = false;

	void update();
	void pauseGame();
	void continueGame();

public:  // Why is the constructor needed if the same is written in the startGame Function?
	Game(): player(Player(&gameBoard, MARIO_SPRITE, MARIO_START_POS)), dk(DonkeyKong(&gameBoard, DONKEY_KONG_SPRITE, DONKEY_KONG_POS)) {}
	void startGame();
};

