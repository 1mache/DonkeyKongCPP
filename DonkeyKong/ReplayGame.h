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
	int currSaveFileId = 0;

	//what the player sees when results doesnt match to what happened in the recording
	void handleResultMismatch(std::pair<size_t, Results::ResultValue> expectedResult, std::pair<size_t, Results::ResultValue> recievedResult);
	// loads steps and results based on current save file id
	bool tryLoadRecordings();

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
	// moves to the next recorded level
	bool moveToNextLevel() override;
	// in this implementation the check is based on recording files instead of level files
	bool hasMoreLevels() const override
	{
		return currSaveFileId < stepsFileNames.size();
	}
	// checks if the something should have happened in the iteration based on results.
	// happens every Game::update
	bool validateLastIteration() override;

public:
																					// games that are replayed are not recorded
	ReplayGame(const std::vector<std::string>& _levelFileNames) : Game(_levelFileNames, currSaveFileId, false) {};
	// sets up all the variables essential for playing the recordings before calling the base start
	bool start() override;
};