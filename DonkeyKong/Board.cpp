#include "Board.h"

void Board::resetBoard() {
	for (int row = 0; row < HEIGHT; row++)
	{
		for (int col = 0; col < WIDTH+1; col++)
		{
			if (col == WIDTH)
				currentBoard[row][col] = '\0';
			else
				currentBoard[row][col] = originalBoard[posToIndex(Point(col, row))];
		}
	}
}

void Board::print() const {
	// dont print the board in silent mode
	if (Constants::isSilentModeOn())
		return;
	
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
	currentBoard[y][x] = originalBoard[posToIndex(position)];
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
	for (char enemyChar : HAZARDS)
	{
		if (enemyChar == charAtPos)
		{
			return true;
		}
	}

	return false;
}

bool Board::isHammerEnemyAtPos(Point position) const
{
	// for each enemy destroyable by hammer check if its in the position
	char charAtPos = getCharAtPos(position);
	for (char enemyChar : HAMMER_ENEMIES)
	{
		if (enemyChar == charAtPos)
		{
			return true;
		}
	}

	return false;
}

Point Board::getWayUpInRow(Point pos)
{
	int row = pos.getY();
	int col = pos.getX();

	bool continuousLeft = true;
	bool continuousRight = true;

	// search closest way up (ladder) from pos outwards that has shared floor to pos (continuous)
	for (int offset = 0; ((col - offset >= 0) && continuousLeft)
		|| ((col + offset < Constants::SCREEN_WIDTH) && continuousRight); ++offset)
	{
		// Check left side
		if ((col - offset >= 0) && continuousLeft)
		{
			Point leftPos(col - offset, row);

			// if the left floor is continuous
			if (isObstacleAtPos(leftPos.oneBelow()))
			{
				if (isLadderAtPos(leftPos))
				{
					return leftPos;
				}
			}

			// else, stop searching left half
			else
			{
				continuousLeft = false;
			}
		}

		// Check right side
		if ((col + offset < Constants::SCREEN_WIDTH) && continuousRight)
		{
			Point rightPos(col + offset, row);

			// if the right floor is continuous
			if (isObstacleAtPos(rightPos.oneBelow()))
			{
				if (isLadderAtPos(rightPos))
				{
					return rightPos;
				}
			}

			// else, stop searching right half
			else
			{
				continuousRight = false;
			}
		}
	}

	// if way up not found
	return Constants::POS_NOT_SET;
}

Point Board::getWayDownInRow(Point pos)
{
	int row = pos.getY();
	int col = pos.getX();
	Point checkPos = pos;

	// search closest way up (ladder) from pos outwards that has shared floor to pos (continuous)
	for (int offset = 0; (col - offset >= 0) || (col + offset < Constants::SCREEN_WIDTH); ++offset)
	{
		// Check left side
		if (col - offset >= 0)
		{
			Point leftPos(col - offset, row);

			if (!isObstacleAtPos(leftPos.oneBelow()) || isLadderAtPos(leftPos.oneBelow().oneBelow()))
			{
				return leftPos;
			}
		}

		// Check right side
		if (col + offset < Constants::SCREEN_WIDTH)
		{
			Point rightPos(col + offset, row);

			if (!isObstacleAtPos(rightPos.oneBelow()) || isLadderAtPos(rightPos.oneBelow().oneBelow()))
			{
				return rightPos;
			}
		}
	}

	// if way down not found
	return Constants::POS_NOT_SET;
}
