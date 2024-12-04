#include "Movement.h"

void Movement::move(int moveX, int moveY, bool useGravity, bool ignoreObstacles)
{
    erase();

    int newX = position.x + moveX;
    int newY = position.y + moveY;
    
    //remember previous position before we change it 
    Point prevPosition = position;
    
    // Move on X and Y axis independently
    if (canMoveToNewPos(newX, position.y) || ignoreObstacles)
    {
        position = { newX, position.y };
    }

    if (canMoveToNewPos(position.x, newY) || ignoreObstacles)
    {
        position = { position.x, newY };
    }

    if (useGravity)
    {
        gravity();
    }

    //check if the char the object stepped on previously wasnt an empty space 
    char charAtPrevPosition = gameBoard->getCharInPos(prevPosition.x, prevPosition.y);
    if (charAtPrevPosition != ' ')
        // and draw it where we stepped on it
        draw(prevPosition ,charAtPrevPosition);

    draw();
}