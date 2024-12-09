#include "Board.h"

void Board::reset() {
	for (int i = 0; i < HEIGHT; i++) {
		memcpy(currentBoard[i], originalBoard[i], WIDTH + 1);
	}
}

void Board::print() const {
	for (int i = 0; i < HEIGHT-1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[HEIGHT - 1];
}

bool Board::isObstacleAtPos(Point position) const
{
	bool isObstacle = false;
	int charAtNewPos = getCharAtPos(position);

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
