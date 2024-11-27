#pragma once
#include "Board.h"

//class Player;

class Game
{
	//Player* pPlayer = nullptr;
	Board* pGameBoard = nullptr;

public:
	//Game(Player* _pPlayer, Board* _pBoard): pPlayer(_pPlayer), pGameBoard(_pBoard)
	Game(Board* _pBoard): pGameBoard(_pBoard)
	{
		//Create the board here or get it as an arg
		pGameBoard->reset();

		// set default position for the player ?
	}

	void drawBoard()
	{
		pGameBoard->print();
		//Maybe additional logic here
	}
};

