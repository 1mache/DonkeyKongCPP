#include "Board.h"

void Board::resetBoard() {
	for (int i = 0; i < HEIGHT; i++) {
		memcpy(currentBoard[i], (*originalBoard)[i], WIDTH + 1);
	}
}

void Board::print() const {
	for (int i = 0; i < HEIGHT-1; i++) {
		std::cout << currentBoard[i] << '\n';
		//animation frame dalay
		Sleep(PRINT_DELAY);
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
	// take the char that was at the original board and put it at current
	currentBoard[y][x] = (*originalBoard)[y][x];
}

bool Board::isObstacleAtPos(Point position) const
{
	// for each obstacle check if its in the position
	char charAtPos = getCharAtPos(position);
	for (char obstacleChar : OBSTACLES)
	{
		if (obstacleChar == charAtPos)
		{
			return true;
		}
	}

	return false;
}

bool Board::isHazardAtPos(Point position) const
{
	// for each hazard check if its in the position
	char charAtPos = getCharAtPos(position);
	for (char hazardChar : HAZARDS)
	{
		if(hazardChar == charAtPos)
		{
			return true;
		}
	}

	return false;
}
