#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>
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
#include "Steps.h"
#include "Results.h"

class Game
{
private:
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
	struct KeyInput
	{
		char key1 = Constants::KEY_NOT_SET, key2 = Constants::KEY_NOT_SET;
		
		KeyInput() = default;
		KeyInput(const std::pair<char, char>& pair): key1(pair.first), key2(pair.second){};
		
		bool notSet()
		{
			return key1 == Constants::KEY_NOT_SET && key2 == Constants::KEY_NOT_SET;
		}

		std::pair<char, char> toPair()
		{
			return std::pair(key1, key2);
		}
	};

	// sets the current level to be of the same tag like the filename passed to it
	// returns if it was successful. see: ReplayGame.start() for use case
	bool trySetCurrLevelByTag(const std::string& filename);
	// waits until user presses enter
	void getPlayerConfirmation() const;
	// prints the message to screen then waits until user presses ENTER 
	void handleError(std::string errorMsg) const
	{
		clearScreen();
		std::cout << errorMsg;
		getPlayerConfirmation();
	}
	void resetIterationCounter()
	{
		iterationCounter = 0;
	}
	// virtual function that tells us if the game has more levels to load
	virtual bool hasMoreLevels() const
	{
		return currLevelId < levelFileNames.size();
	}
	// what happens when Mario gets hurt, returns false if he dies true otherwise
	virtual bool handleStrike();
	// what happens when Mario reaches Pauline
	virtual void levelWon();
	// returns if succeeded to move to next level 
	virtual void moveToNextLevel();
	// this is irrelevant for regular game, where every iteration is valid
	virtual bool validateLastIteration() 
	{
		return true;
	}
private:
	// will the game be recorded
	const bool recorded;
	Steps recSteps;
	Results recResults;

	//will be set when we read from file
	Point marioStartPos = Constants::POS_NOT_SET;
	Point donkeyKongPos = Constants::POS_NOT_SET;
	Point paulinePos = Constants::POS_NOT_SET;
	Point legendPos = Constants::POS_NOT_SET;
	Point hammerPos = Constants::POS_NOT_SET;

	std::vector<std::pair<Point, char>> ghostsStartPositions;
	
	// reference to a vector of file names
	const std::vector<std::string>& levelFileNames;
	// which level are we on (id)
	int currLevelId;
	// counts iterations
	size_t iterationCounter = 0;

	Board* gameBoard = nullptr;
	Player* player = nullptr;

	GhostsManager* ghostsManager = nullptr;
	BarrelManager* barrelManager = nullptr;

	int lives = MAX_LIVES;
	int score = 0;

	bool isPaused = false;


	void displayLevelException(LevelFileException& e);

	// draws the hammer in hammerPos
	void drawHammer();

	// show lives and score on screen
	void updateLegend() const;

	// deletes ghost manager and creates new one if needed
	void resetGhostsManager();

	void pauseGame();

	void continueGame();

	// game loop
	void update();

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
	// virtual function that gets 2 keys of input
	virtual KeyInput getInputKeys();
	// virtual function that sets the random seed either by time or from file 
	virtual void setRandSeed()
	{
		long seed = time(0);
		if(recorded)
			recSteps.setRandomSeed(seed);
		srand(seed);
	}

	void saveSteps();
	void saveResults();

public:
	Game(const std::vector<std::string>& _levelFileNames, int startLevelId, bool _recorded) : 
		levelFileNames(_levelFileNames), currLevelId(startLevelId), recorded(_recorded) {};
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete; 
	virtual ~Game()
	{
		delete gameBoard;
		delete player;
		delete barrelManager;
		delete ghostsManager;
	}
	
	// utility function:
	// for a level fileName "dkong_01.screen" returns the "01" part
	static std::string getLevelTag(const std::string& levelFileName) 
	{
		size_t prefixSize = std::strlen(Constants::FILENAME_PREFIX);
		size_t extStartId = levelFileName.find_first_of('.');

		return levelFileName.substr(prefixSize, extStartId - prefixSize);
	}

	virtual bool start();

	virtual void resetLevel();

	int getScore() const
	{
		return score;
	}
	size_t getIterationCounter() const 
	{
		return iterationCounter;
	}
};