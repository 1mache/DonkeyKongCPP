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

	Game::KeyInput getInputKeys() const override;
	
	void setRandSeed() override
	{
		long seed = steps.getRandomSeed();
		srand(seed);
	}
public:
																					// games that are replayed are not recorded
	ReplayGame(const std::vector<std::string>& _levelFileNames) : Game(_levelFileNames, currStepsFileId, false) {};
	
	bool start() override;
	
	//void resetLevel() override
	//{
	//	int curLevel = getCurrentLevel();
	//	steps = Steps::loadSteps(stepsFileNames[curLevel]);
	//	results = Results::loadResults(resultsFileNames[curLevel]);

	//	Game::resetLevel();
	//}
};