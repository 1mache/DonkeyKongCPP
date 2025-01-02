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

private:
	static constexpr char SCREEN_BORDER = 'Q';
	static constexpr char LADDER = 'H';
	// objects that mario cannot pass through
	static constexpr char OBSTACLES[] = { '>', '<', '=', 'W', SCREEN_BORDER};
	// things that kill mario
	static constexpr char HAZARDS[] = { BARREL, EXPLOSION };

	static constexpr int WIDTH = Constants::SCREEN_WIDTH;
	static constexpr int HEIGHT = Constants::SCREEN_HEIGHT;
	// how much delay there is in printing animation
	static constexpr int PRINT_DELAY = 20;

	const char* originalBoard[HEIGHT] = {
		// 00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                                      $ ~ (SAVE ME!)              _   _       Q", // 1
		  "Q                                 ============                    ( \\/ )       Q", // 2
		  "Q                                 H    &     H                     \\  / -      Q", // 3
		  "Q                            <<<<<<<<<<=>>>>>>>>>>>                 \\/         Q", // 4
		  "Q                            H                    H                            Q", // 5
		  "Q                            H                    H                            Q", // 6
		  "Q                            H                    H                            Q", // 7
		  "Q            =<<<<<<<<<<<<<<<======================>>>>>>>>>>>>>>>=            Q", // 8
		  "Q            H                                                    H            Q", // 9
		  "Q            H                      <=====>                       H            Q", // 10
		  "Q            H                         H                          H            Q", // 11
		  "Q>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> H <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 12
		  "Q                                      H                                       Q", // 13
		  "Q                                      H                              =========Q", // 14
		  "Q                                      H                                  H    Q", // 15
		  "Q     ==<<==<<==<<==<<==<<==<<==<<==<<<=>>>==>>==>>==>>==>>==>>==>>==     H    Q", // 16
		  "Q                             W                                     W     H    Q", // 17
		  "Q>>>>>>>>>>>>>>>>>>>>>>>>>>   W    =============================    W     H    Q", // 18
		  "Q                             W       W 0  MTA Pizzeria  0  W       W     H    Q", // 19
		  "Q     <<<<<<<<<<<<<<<<<<<<<<<<====    W---------------------W    ====     H    Q", // 20
		  "Q        H                            W  ____  __     _     W             H    Q", // 21
		  "Q        H                         ===W  0PEN |  |   [+]    W===          H    Q", // 22
		  "Q        H                            W       |  |                        H    Q", // 23
		  "Q==============================================================================Q"  // 24
	};

	char currentBoard[HEIGHT][WIDTH + 1]; // +1 for null terminator
public:
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

