#include "ReplayGame.h"

void ReplayGame::handleResultMismatch(std::pair<size_t, Results::ResultValue> expectedResult, std::pair<size_t, Results::ResultValue> recievedResult)
{
	std::ostringstream errorMsgStream;
	errorMsgStream << "Error: Results file doesnt match the steps file: "<< stepsFileNames[currSaveFileId] << std::endl;

	// if we expected something to happen on this iteration but nothing happened
	if(recievedResult.second == Results::NO_RESULT)
	{
		errorMsgStream << "Nothing happened on iteration: " << recievedResult.first
			<< " but based on results file the player " << Results::resultToStr(expectedResult) << std::endl;
	}
	// if there is a mismatch in the result kind
	else if (recievedResult.second != expectedResult.second)
	{
		// if there is no next result in the results file
		if (expectedResult.second == Results::NO_RESULT)
			errorMsgStream << "No results left in " << resultsFileNames[currSaveFileId] << std::endl;
		else
		{
			errorMsgStream << "Next result is " << Results::resultToStr(expectedResult) << " but player "
				<< Results::resultToStr(recievedResult);
		}
	}
	// if the mismatch is in the iteration numbers
	else if (recievedResult.first != expectedResult.first)
	{
		errorMsgStream << "Iteration doesnt match, player " << Results::resultToStr(recievedResult)
			<< " instead of " << expectedResult.first;
	}
	
	// different message based on of its the last level
	if (currSaveFileId == stepsFileNames.size() - 1)
		errorMsgStream << std::endl << "This was the last level, Press ENTER to end the recording";
	else
		errorMsgStream << std::endl << "Press ENTER to move to next level";

	handleError(errorMsgStream.str());
}

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
	std::pair<size_t, Results::ResultValue> result = {iteration, resultType};
	auto expectedResult = results.popResult();
	if (result != expectedResult)
	{
		handleResultMismatch(expectedResult, result);
		moveToNextLevel();
		return false;
	}

	return survived;
}

void ReplayGame::levelWon()
{
	size_t iteration = getIterationCounter();
	Results::ResultValue resultType = Results::FINISHED;

	std::pair<size_t, Results::ResultValue> result  = { iteration, resultType };
	auto expectedResult = results.popResult();
	if (result != expectedResult)
		handleResultMismatch(expectedResult, result);
	
	addWinScoreReward();
	moveToNextLevel();
}

void ReplayGame::moveToNextLevel()
{
	currSaveFileId++;
	resetIterationCounter();

	// if we still have levels
	if(hasMoreLevels())
	{
		// set the next loaded level to be one of the same tag as 
		std::string nextLevelTag = Game::getLevelTag(stepsFileNames[currSaveFileId]);
		if (!trySetCurrLevelByTag(nextLevelTag))
		{
			std::ostringstream errorMsgStream;
			errorMsgStream << "Error: \".screen\" file for the tag: " << nextLevelTag
				<< " not found. Check the working directory:" << std::endl << getWorkingDirectoryStr() << std::endl;
			handleError(errorMsgStream.str() + "Press ENTER to move to continue the recording");
			// try to move to next level, if there is no next level this will return false
			moveToNextLevel();
		}

		// if we got here then we successfully moved to next level
		loadRecordings();

		setRandSeed();
	}
}

bool ReplayGame::validateLastIteration()
{
	size_t iteration = getIterationCounter();
	// this will only be true if nothing happened and there is a result that should
	// happen on this iteration
	if (results.hasResultOnIteration(iteration))
	{
		auto expectedResult = results.popResult();
		std::pair<size_t, Results::ResultValue> noResult = { iteration, Results::NO_RESULT };
		// tell the user and go to next level
		handleResultMismatch(expectedResult, noResult);
		moveToNextLevel();
		
		return false;
	}

	return true;
}

bool ReplayGame::start()
{
	// get all the results and steps fileNames
	readFileNames(stepsFileNames, GameOptions::STEPS_FILE_EXT);
	readFileNames(resultsFileNames, GameOptions::RESULTS_FILE_EXT);
	loadRecordings();

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
		std::string firstLevelTag = Game::getLevelTag(stepsFileNames[currSaveFileId]);
		// if for some reason there is no level file for the first recording
		if (!trySetCurrLevelByTag(firstLevelTag))
		{
			errorMsgStream << "Error: \".screen\" file for the tag: " << firstLevelTag
				<< " not found. Check the working directory:" << std::endl << getWorkingDirectoryStr() << std::endl;

			// tell the player
			handleError(errorMsgStream.str() + "Press ENTER to continue");
			// try to move to next level, if there are more recordings
			moveToNextLevel();
			// then start the game as usual
			return Game::start();
		}
	}
	
	
	// if there was an error there will be an error message, so print it using the function and end the game
	std::string errorMsg = errorMsgStream.str();
	if (!errorMsg.empty())
	{
		handleError(errorMsg + "Press ENTER to end the recording");
		return false;
	}

	return Game::start();
}
