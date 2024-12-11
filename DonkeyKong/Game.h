#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "Menu.h"

class Game
{
	static constexpr int ESC = 27;
	static constexpr char MARIO_SPRITE = '@';
	static constexpr Point START_POS = {2, 23};
	static constexpr Point PAUSEMESSAGE_POS = {31, 2};
	// ChatGPT said that this is the way for static constexpr string
	static constexpr const char* PAUSE_MESSAGE = "Game Paused: Press ESC to continue";

	Board gameBoard;
	Player player;

	bool isPaused = false;
	bool gameOver = false;

	void update();
	void pauseGame();
	void continueGame();

public:
	Game(): player(Player(&gameBoard, MARIO_SPRITE, START_POS)) {}
	void startGame();
};

