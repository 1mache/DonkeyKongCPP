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
	static constexpr Point START_POS = {2, 22};

	Board gameBoard;
	Player player;

	void update();
	void endGame();
	void pauseGame();
	void continueGame();

public:
	Game(): player(Player(&gameBoard, MARIO_SPRITE, START_POS)) {}
	void startGame();
};

