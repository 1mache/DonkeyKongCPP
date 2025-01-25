#pragma once
#include "Game.h"

class ReplayGame: public Game
{
	const std::vector<std::string>& stepsFileNames;
	const std::vector<std::string>& resultsFileNames;

	Steps steps;
	Results results;

	Game::KeyInput getInputKeys() const override;
	
	void setRandSeed() override
	{
		long seed = steps.getRandomSeed();
		srand(seed);
	}
public:
																					// games that are replayed are not recorded
	ReplayGame(const std::vector<std::string>& _levelFileNames, int startLevelId) : Game(_levelFileNames, startLevelId, false) {};
	
	void resetLevel() override
	{
		int curLevel = getCurrentLevel();
		steps = Steps::loadSteps(stepsFileNames[curLevel]);
		results = Results::loadResults(resultsFileNames[curLevel]);

		Game::resetLevel();
	}
};