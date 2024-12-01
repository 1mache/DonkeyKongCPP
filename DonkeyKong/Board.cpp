#include <cstring>
#include <iostream>

#include "Board.h"

void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void Board::print() const {
	for (int i = 0; i < MAX_Y-1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}

bool Board::isPosAnObstacle(int x, int y) const
{
	bool isObstacle = false;
	int charAtNewPos = getCharInPos(x, y);

	for (size_t i = 0; i < NUM_OBSTACLES; i++)
	{
		if (charAtNewPos == OBSTACLES[i])
		{
			isObstacle = true;
			break;
		}
	}

	return isObstacle;
}
