#pragma once

class Board {
	static constexpr int MAX_X = 80;
	static constexpr int MAX_Y = 25;
	static constexpr char SCREEN_BORDER = 'Q';
	static constexpr char OBSTACLES[] = { '>', '<', '=', 'Q'};
	static constexpr size_t NUM_OBSTACLES = sizeof(OBSTACLES) / sizeof(OBSTACLES[0]);

	const char* originalBoard[MAX_Y] = {
		// 00000000001111111111222222222233333333334444444444555555555566666666667777777777    
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
		  "Q                      $                                                       Q", // 1
		  "Q                 =========                                                    Q", // 2
		  "Q        &        H       H                                                    Q", // 3
		  "Q===============================                                               Q", // 4
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
		  "Q<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Q", // 23
		  "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
	};

	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
public:
	void reset();
	void print() const;

	int getObstacleArraySize() const { return NUM_OBSTACLES; }
	char obstacleArrayGet(int id) const { return OBSTACLES[id]; }

	char getChar(int x, int y) const { return currentBoard[y][x]; }

	bool isPosInBounds(int x, int y) const { return !((x < 0 || MAX_X < x) || (y < 0 || MAX_Y < y)); }
};

