#pragma once
#include <cstring>
#include <iostream>
#include <windows.h>
#include "Point.h"
#include "Constants.h"

class Board {
public:
	static constexpr char BARREL = 'O';
	static constexpr char EXPLOSION = '*';
	static constexpr char DONKEY_KONG = '&';
	static constexpr char PAULINE = '$';

private:
	static constexpr char SCREEN_BORDER = 'Q';
	static constexpr char LADDER = 'H';
	// objects that mario cannot pass through
	static constexpr char OBSTACLES[] = { '>', '<', '=', 'W', SCREEN_BORDER };
	// things that kill mario
	static constexpr char HAZARDS[] = { BARREL, EXPLOSION };

	static constexpr int WIDTH = Constants::SCREEN_WIDTH;
	static constexpr int HEIGHT = Constants::SCREEN_HEIGHT;
	// how much delay there is in printing animation
	static constexpr int PRINT_DELAY = 20;
	
	const char (*const originalBoard)[HEIGHT][WIDTH + 1];

	char currentBoard[HEIGHT][WIDTH + 1] = {}; // +1 for null terminator
public:
	Board(const char (*const _originalBoard)[HEIGHT][WIDTH + 1]): originalBoard(_originalBoard)
	{};
	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;
	~Board()
	{
		delete[] originalBoard;
	}

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

	bool isLadderAtPos(Point position)const 
	{ 
		return getCharAtPos(position) == LADDER; 
	}
};

