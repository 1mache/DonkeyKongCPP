#pragma once
#include <iostream>
#include <windows.h>
#include <filesystem>
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
#include "LevelFileException.h"

class Game
{
	static constexpr int ESC = 27;
	static constexpr char ENTER = '\r';
	static constexpr char MARIO_SPRITE = '@';
	static constexpr char LEGEND_CHAR = 'L';

	static constexpr Point LIVES_COUNTER_POS = { 74, 3 };
	static constexpr const char* PAUSE_MESSAGE = "Game Paused";
	static constexpr int MAX_LIVES = 3;
	static constexpr int ENEMY_SCORE_AMOUNT = 25;
	static constexpr int PRINCESS_SCORE_AMOUNT = 100;

protected:
	
	static constexpr char KEY_NOT_SET = -1;
	struct KeyInput
	{
		char key1 = KEY_NOT_SET, key2 = KEY_NOT_SET;
		bool notSet()
		{
			return key1 == KEY_NOT_SET && key2 == KEY_NOT_SET;
		}
	};

private:
	//will be set when we read from file
	Point marioStartPos = Constants::POS_NOT_SET;
	Point donkeyKongPos = Constants::POS_NOT_SET;
	Point paulinePos = Constants::POS_NOT_SET;
	Point legendPos = Constants::POS_NOT_SET;
	Point hammerPos = Constants::POS_NOT_SET;

	std::vector<Point> ghostsStartPositions;
	
	// reference to a vector of file names
	const std::vector<std::string>& levelFileNames;
	// which level are we on (id)
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
	// waits until user presses enter
	void getPlayerConfirmation() const;

	void displayException(LevelFileException& e);

	// draws the hammer in hammerPos
	void drawHammer();

	// what happens when mario gets hurt
	bool handleStrike();
	// show lives and score on screen
	void updateLegend() const;

	// deletes ghost manager and creates new one if needed
	void resetGhostsManager();

	void pauseGame();

	void continueGame();

	//reads all the necessary info from level file and "builds" the board, returns the board if was successful 
	Board* readLevelFromFile(const std::string& filename);
	// sets all the entity positions to not set
	void resetEntitiesPositions();
	// gets a char and if its one of the chars that are relevant to game, sets their position
	// returns if the char should be added to board (we dont always want that)
	bool setEntityPositionByChar(char c, Point position);
	// given ifstream object iterates until EOF or end of line \n 
	void discardRestOfLine(std::ifstream& levelFile);
	// checks if some entity position wasnt set and returns its name via output parameter
	bool isEntityMissing(std::string& outEntityMissing);
	// checks if player hit something that can be killed with a hammer and if so destroys it
	void checkPlayerHitEnemy();

	virtual KeyInput getInputKeys() const;
	virtual void setRandSeed() const
	{
		srand(time(0)); // gets us a new seed for use in rand
	}

public:
	Game(const std::vector<std::string>& _levelFileNames, int startLevelId) : levelFileNames(_levelFileNames), currLevel(startLevelId) {};
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete; 
	virtual ~Game()
	{
		delete gameBoard;
		delete player;
		delete barrelManager;
		delete ghostsManager;
	}
	
	virtual bool start();

	void resetLevel();

	int getScore() const
	{
		return score;
	}
};