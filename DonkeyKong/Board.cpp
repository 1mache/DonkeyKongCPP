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

char Board::getCharAtPos(Point position) const
{
	int x = position.getX();
	int y = position.getY();

	if((x >= 0 && x < WIDTH)
		&& (y >= 0 && y < HEIGHT))
	{
		return currentBoard[y][x];
	}
	else
	{
		//if point out of screen bounds return screen border
		return SCREEN_BORDER;
	}
}

void Board::updateBoardWithChar(Point position, char newChar)
{
	int x = position.getX();
	int y = position.getY();

	currentBoard[y][x] = newChar;
}

void Board::resetCharAtPos(Point position)
{
	int x = position.getX();
	int y = position.getY();

	currentBoard[y][x] = originalBoard[y][x];
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
