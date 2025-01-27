#include "GameManager.h"

int main(int argc, char* argv[]) 
{
	GameManager gameManager;
	if (argc > 1 && std::string(argv[1]) == "-save")
	{
		gameManager.launchGame(GameManager::GameMode::SAVE);
	}
	else if(argc > 1 && std::string(argv[1]) == "-load")
	{

		gameManager.launchGame(GameManager::GameMode::LOAD);
	}
	else
		gameManager.launchGame(GameManager::GameMode::STANDARD);
}