#pragma once
#include "Game.h"
#include "Steps.h"
#include "Results.h"

class ReplayGame: public Game
{
	Steps steps;
	Results results;

	const std::vector<std::string>& stepsFileNames;
	const std::vector<std::string>& resultsFileNames;


	Game::KeyInput getInputKeys() const override;
	void setRandSeed() const override;
public:
	ReplayGame(const std::vector<std::string>& _levelFileNames, int startLevelId) : Game(_levelFileNames, startLevelId) {};
	
	bool start() override
	{
		// something like that, maybe in resetLevel instead 
		steps = Steps::loadSteps(stepsFileNames[0]);
		results = Results::loadResults(resultsFileNames[0]);
		Game::start();
	}
};