#include "ReplayGame.h"

Game::KeyInput ReplayGame::getInputKeys()
{
	// empty input with both keys not set
	KeyInput input;
	size_t iteration = getIterationCounter();

	if (steps.isNextStepOnIteration(iteration))
		input = steps.popStep();

	return input;
}

bool ReplayGame::handleStrike()
{
	size_t iteration = getIterationCounter();
	bool survived = Game::handleStrike();

	// set result type based on if player survived
	Results::ResultValue resultType = survived ? Results::LOST_LIFE : Results::DIED;
	std::pair<size_t, Results::ResultValue> expectedResult = {iteration, resultType};
	auto nextResult = results.popResult();
	if(expectedResult != nextResult)
	{
		// TODO: display error message then move to next level
	}

	return survived;
}

void ReplayGame::levelWon()
{
	size_t iteration = getIterationCounter();
	Results::ResultValue resultType = Results::FINISHED;
	std::pair<size_t, Results::ResultValue> expectedResult = { iteration, resultType };
	auto nextResult = results.popResult();
	if (expectedResult != nextResult)
	{
		// TODO: display error message then move to next level
	}
}

void ReplayGame::moveToNextLevel()
{
	currStepsFileId++;
	// TODO: probably use setByTag instead of base
	Game::moveToNextLevel();
}

bool ReplayGame::start()
{
	// get all the results and steps fileNames
	readFileNames(stepsFileNames, Constants::STEPS_FILE_EXT);
	readFileNames(resultsFileNames, Constants::RESULTS_FILE_EXT);
	
	std::ostringstream errorMsgStream;
	if (stepsFileNames.size() == 0)
		errorMsgStream << "No \".steps\" files found to load. Check the working diretory:" << std::endl
		<< getWorkingDirectoryStr();

	else if (stepsFileNames.size() != resultsFileNames.size())
		errorMsgStream << "Error: The number of \".steps\" files and \".results\" files are not matching." << std::endl;

	else
	{
		// set the base Game`s first level to be the same tag as the first steps file
		// if the first steps file is dkong_01.steps we want game to load dkong_01.screen as the first level
		std::string firstLevelTag = Game::getLevelTag(stepsFileNames[currStepsFileId]);
		if (!trySetCurrLevelByTag(firstLevelTag))
			errorMsgStream << "Error: \".screen\" file for the tag: " << firstLevelTag
			<< " not found. Check the working directory:" << std::endl << getWorkingDirectoryStr();
	}
	
	
	// if there was an error there will be an error message, so print it using the function and end the game
	std::string errorMsg = errorMsgStream.str();
	if (!errorMsg.empty())
	{
		handleError(errorMsg + "Press ENTER to exit game");
		return false;
	}

	return Game::start();
}
