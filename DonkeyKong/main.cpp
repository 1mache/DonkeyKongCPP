#include "GameManager.h"

int main(int argc, char* argv[]) 
{
	GameManager gameManager;
	if (argc > 1 && std::string(argv[1]) == "-save")
	{
		gameManager.setMode(GameManager::GameMode::SAVE);
	}
	else if(argc > 1 && std::string(argv[1]) == "-load")
	{
		gameManager.setMode(GameManager::GameMode::LOAD);
	}

	gameManager.launchGame();
}