#include <iostream>
#include <windows.h>
#include <conio.h>

#include "utils.h"
#include "Board.h"
#include "Game.h"

int main(int argc, char* argv[]) 
{
	Board gameBoard;

	Game game(&gameBoard);

	game.drawBoard();

	//game loop
	while(true)
	{
		Sleep(50);
	}
}