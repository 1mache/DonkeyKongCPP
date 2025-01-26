#include "ReplayGame.h"

bool ReplayGame::start()
{
	// get all the results and steps fileNames
	readFileNames(stepsFileNames, Constants::STEPS_FILE_EXT);
	readFileNames(resultsFileNames, Constants::RESULTS_FILE_EXT);
	if (stepsFileNames.size() == 0)
	{
		std::cout << "Error: No \".steps\" files found to load. Check the working diretory." << std::endl;
		getPlayerConfirmation();
		return false;
	}
	if (stepsFileNames.size() != resultsFileNames.size())
	{
		std::cout << "Error: The number of \".steps\" files and \".results\" files are not matching." << std::endl;
		getPlayerConfirmation();
		return false;
	}
	// set the base Game`s first level to be the same tag as the first steps file
	// if the first steps file is dkong_01.steps we want game to load dkong_01.screen as the first level
	setCurrLevelByTag(stepsFileNames[currStepsFileId]);

	Game::start();
}
