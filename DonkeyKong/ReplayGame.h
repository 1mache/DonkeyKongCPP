#pragma once
#include "Game.h"

class ReplayGame: public Game
{
	std::vector<std::string> stepsFileNames;
	std::vector<std::string> resultsFileNames;

	Steps steps;
	Results results;
	// this is different from a simmilar variable in base class Game as there
	// isnt necessarily a recording for every level
	int currStepsFileId = 0;

	Game::KeyInput getInputKeys() override;
	
	void setRandSeed() override
	{
		long seed = steps.getRandomSeed();
		srand(seed);
	}

	//in addition to base class implementation, checks if there is a matching event in results file
	bool handleStrike() override;
	//in addition to base class implementation, checks if there is a matching event in results file
	void levelWon() override;
	void moveToNextLevel() override;

public:
																					// games that are replayed are not recorded
	ReplayGame(const std::vector<std::string>& _levelFileNames) : Game(_levelFileNames, currStepsFileId, false) {};
	
	bool start() override;
	
	void resetLevel() override
	{
		steps = Steps::loadSteps(stepsFileNames[currStepsFileId]);
		results = Results::loadResults(resultsFileNames[currStepsFileId]);

		Game::resetLevel();
	}
};