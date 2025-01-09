#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>

#include "Board.h"
#include "Player.h"
#include "Point.h"
#include "Menu.h"
#include "Barrel.h"
#include "BarrelManager.h"
#include "GhostsManager.h"
#include "Constants.h"

class Game
{
	static constexpr int ESC = 27;
	static constexpr char MARIO_SPRITE = '@';
	static constexpr char LEGEND_CHAR = 'L';

	static constexpr Point LIVES_COUNTER_POS = { 74, 3 };
	static constexpr const char* PAUSE_MESSAGE = "Game Paused";
	static constexpr int MAX_LIVES = 3;

	//will be set when we read from file
	Point marioStartPos = Constants::POS_NOT_SET;
	Point donkeyKongPos = Constants::POS_NOT_SET;
	Point paulinePos = Constants::POS_NOT_SET;
	
	// reference to a vector of file names
	const std::vector<std::string>& levelFileNames;
	int currLevel;

	Board* gameBoard = nullptr;
	Player* player = nullptr;

	GhostsManager* ghostsManager = nullptr;
	BarrelManager* barrelManager = nullptr;

	int lives = MAX_LIVES;
	int score = 0;

	bool isPaused = false;

	// game loop
	void update();

	// what happens when mario gets hurt
	bool handleStrike();
	// lives and score
	void updateLegend() const;

	void pauseGame();

	void continueGame();

	//reads all the necessary info from level file and "builds" the board, returns the board if was successful 
	Board* readLevelFromFile(const std::string& filename);
	// gets a char and if its one of the chars that are relevant to game, sets their position
	// returns if the char should be added to board (we dont always want that)
	bool setEntityPositionByChar(char c, Point position);
	// given ifstream object iterates until EOF or end of line \n 
	void discardRestOfLine(std::ifstream& levelFile);

public:
	Game(const std::vector<std::string>& _levelFileNames, int startLevelId) : levelFileNames(_levelFileNames), currLevel(startLevelId) {};
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete; 
	~Game()
	{
		delete gameBoard;
		delete player;
		delete barrelManager;
		delete ghostsManager;
	}
	
	bool start();

	void resetLevel();

	void checkPlayerHitHammerEnemy();
};