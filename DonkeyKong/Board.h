#pragma once
#include <cstring>
#include <iostream>
#include <windows.h>
#include <vector>
#include "Point.h"
#include "Constants.h"

class Board {
public:
	static constexpr char BARREL = 'O';
	static constexpr char EXPLOSION = '*';
	static constexpr char GHOST = 'x';
	static constexpr char CLIMBING_GHOST = 'X';
	static constexpr char DONKEY_KONG = '&';
	static constexpr char PAULINE = '$';
	static constexpr char HAMMER = 'p';
	static constexpr char BLANK_SPACE = ' ';
	static constexpr char DEFAULT_FLOOR = '=';

	// function that translates 2D position to an index in originalBoard
	static int posToIndex(Point point)
	{
		return (point.getY()* Constants::SCREEN_WIDTH) + point.getX();
	}

private:
	static constexpr char SCREEN_BORDER = 'Q';
	static constexpr char LADDER = 'H';
	// objects that mario cannot pass through
	static constexpr char OBSTACLES[] = { '>', '<', DEFAULT_FLOOR, 'W', SCREEN_BORDER };
	// things that kill mario
	static constexpr char HAZARDS[] = { BARREL, EXPLOSION, GHOST };

	static constexpr char HAMMER_ENEMIES[] = { BARREL, GHOST, CLIMBING_GHOST };

	//static constexpr char GHOSTS[] = { GHOST, CLIMBING_GHOST };

	static constexpr int WIDTH = Constants::SCREEN_WIDTH;
	static constexpr int HEIGHT = Constants::SCREEN_HEIGHT;
	// how much delay there is in printing animation
	static constexpr int PRINT_DELAY = 20;
	
	// the original board is now a vector of HEIGHT * WIDTH size that represents 2D board as before, 
	// this makes creating it outside the class and passing it to here easier
	const std::vector<char> originalBoard;

	char currentBoard[HEIGHT][WIDTH + 1] = {}; // +1 for null terminator

	Point playerPos = Constants::POS_NOT_SET;

public:
	Board(std::vector<char>&& _originalBoard): originalBoard(std::move(_originalBoard)) {};

	// resets the entire current board
	void resetBoard();
	void print() const;

	char getCharAtPos(Point position) const;
	
	// puts the given char at given position on current board
	void updateBoardWithChar(Point position, char newChar);
	// resets the char at given position
	void resetCharAtPos(Point position);

	bool isPosInBounds(Point position) const 
	{
		int x = position.getX();
		int y = position.getY();
		return ((0 <= x && x < WIDTH) && (0 <= y && y < HEIGHT)); 
	}

	bool isObstacleAtPos(Point position) const;
	
	bool isHazardAtPos(Point position) const;

	bool isHammerEnemyAtPos(Point position) const;

	bool isLadderAtPos(Point position)const 
	{ 
		return getCharAtPos(position) == LADDER; 
	}

	bool isHammerAtPos(Point position) const
	{
		return getCharAtPos(position) == HAMMER;
	}

	// check if the char at position is a type of ghost from GHOSTS[]
	bool isGhostAtPos(Point position) const;

	void setPlayerPos(Point pos)
	{
		playerPos = pos;
	}

	Point getPlayerPos()
	{
		return playerPos;
	}

	Point getWayUpInRow(Point pos)
	{
		int row = pos.getY();
		int col = pos.getX();

		// for left side from pos that is on continuous floor get closest way up (ladder)
		while (isObstacleAtPos(Point(col, row).oneBelow()) && col > 0)
		{
			if (isLadderAtPos(Point(col, row)))
			{
				return Point(col, row);
			}
			--col;
		}

		col = pos.getX();

		// for right side from pos that is on continuous floor get closest way up (ladder)
		while (isObstacleAtPos(Point(col, row).oneBelow()) && col < Constants::SCREEN_WIDTH)
		{
			if (isLadderAtPos(Point(col, row)))
			{
				return Point(col, row);
			}
			++col;
		}

		//return Constants::POS_NOT_SET;
		return getPlayerPos();
	}

	Point getWayDownInRow(Point pos)
	{
		int row = pos.getY();
		int col = pos.getX();
		Point checkPos = Point(col, row);

		// for left side from pos get closest way down (ladder or hole in floor)
		while (col > 0)
		{
			checkPos = Point(col, row);
			if (!isObstacleAtPos(checkPos) || isLadderAtPos(checkPos.oneBelow().oneBelow()))
			{
				return checkPos;
			}
			--col;
		}

		col = pos.getX();

		// for right side from pos get closest way down (ladder or hole in floor)
		while (col < Constants::SCREEN_WIDTH)
		{
			checkPos = Point(col, row);
			if (!isObstacleAtPos(checkPos) || isLadderAtPos(checkPos.oneBelow().oneBelow()))
			{
				return checkPos;
			}
			++col;
		}

		//return Constants::POS_NOT_SET;
		return getPlayerPos();
	}
};

