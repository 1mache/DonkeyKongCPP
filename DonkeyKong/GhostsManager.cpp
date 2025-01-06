#include "GhostsManager.h"

void GhostsManager::spawnAllGhosts()
{
    // check each char in the board if it's a ghost
    for (int y = 0; y < Constants::SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < Constants::SCREEN_WIDTH; x++)
        {
            Point curPosition = { x, y };

            if (gameBoard->getCharAtPos(curPosition) == gameBoard->GHOST)
            {
                // erase original ghost in board
                gotoScreenPos(curPosition);
                gameBoard->updateCurrentBoardWithChar(curPosition, ' ');
                std::cout << ' ';

                // ghost constructor, creates ghost in the vector 
                ghostsVector.emplace_back(gameBoard, curPosition);
                //ghostsNum += 1;
            }
        }
    }
}

void GhostsManager::manageGhosts()
{
    if (!spawnedGhosts)
    {
        spawnAllGhosts();
        spawnedGhosts = true;
    }

    else
    {
        for (size_t i = 0; i < ghostsVector.size(); i++)
        {
            ghostsVector[i].moveGhost();
        }
    }
}

void GhostsManager::destroyGhostAtPos(Point destroyPos)
{
    for (size_t i = 0; i < ghostsVector.size(); i++)
    {
        if (ghostsVector[i].getPosition() == destroyPos)
        {
            deleteGhost(i);
            break;
        }
    }
}
