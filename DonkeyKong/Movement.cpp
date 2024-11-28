#include "Movement.h"

void Movement::move()
{
    int newX = position.x + direction.x;
    int newY = position.y + direction.y;
    
    int charAtNewPos = gameBoard->getChar(newX, newY);
    int obstacles_size = gameBoard->getObstacleArraySize();
    for (size_t i = 0; i < obstacles_size; i++)
        if ((charAtNewPos == gameBoard->obstacleArrayGet(i)) || gameBoard->isPosInBounds(newX, newY) == false)
            return;

    position.x = newX;
    position.y = newY;
}