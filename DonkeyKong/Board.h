#pragma once
#include <cstring>
#include <iostream>
#include "Point.h"
#include "Constants.h"

class Board {
	static constexpr char SCREEN_BORDER = 'Q';
	static constexpr char LADDER = 'H';
	static constexpr char PAULINE = '$';
	static constexpr char OBSTACLES[] = { '>', '<', '=', 'Q' };
	static constexpr size_t NUM_OBSTACLES = sizeof(OBSTACLES) / sizeof(OBSTACLES[0]);

	static constexpr int WIDTH = Constants::SCREEN_WIDTH;
	static constexpr int HEIGHT = Constants::SCREEN_HEIGHT;

	const char* originalBoard[HEIGHT] = {
		// 00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q      _  _            $                                           _  _        Q", // 1
		  "Q     (_)(_)       =========                                      ( \\/ )       Q", // 2
		  "Q     (_)(_) &     H       H                                       \\  / - 3    Q", // 3
		  "Q===============================                                    \\/         Q", // 4
		  "Q                            H                                                 Q", // 5
		  "Q                            H                                                 Q", // 6
		  "Q                            H                                                 Q", // 7
		  "Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=   =<<<<<<<<<<<<<<<<<<<=                Q", // 8
		  "Q                 H                         H                H                 Q", // 9
		  "Q                 H                         H                H                 Q", // 10
		  "Q                 H                         H                H                 Q", // 11
		  "Q          =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 12
		  "Q                             H                                                Q", // 13
		  "Q                             H                                                Q", // 14
		  "Q                             H                                                Q", // 15
		  "Q                             H                                                Q", // 16
		  "Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>=                                         Q", // 17
		  "Q                                  H                                           Q", // 18
		  "Q                                  H                                           Q", // 19
		  "Q                                 =<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 20
		  "Q                                                H                             Q", // 21
		  "Q                                                H                             Q", // 22
		  "Q                                                H                             Q", // 23
		  "Q==============================================================================Q"  // 24
	};

	char currentBoard[HEIGHT][WIDTH + 1]; // +1 for null terminator
public:
	void reset();
	void print() const;

	char getCharAtPos(Point position) const;

	bool isPosInBounds(Point position) const 
	{
		int x = position.getX();
		int y = position.getY();
		return ((0 < x && x < WIDTH) && (0 < y && y < HEIGHT)); 
	}
	bool isObstacleAtPos(Point position) const;
	bool isLadderAtPos(Point position)const 
	{ 
		return getCharAtPos(position) == LADDER; 
	}
	bool isPaulineAtPos(Point position) const 
	{ 
		return getCharAtPos(position) == PAULINE; 
	}
};

