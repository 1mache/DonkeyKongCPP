#include "Movement.h"

void Movement::move(Point movePosition, bool useGravity, bool ignoreObstacles)
{
    erase();

    int newX = position.getX() + movePosition.getX();
    int newY = position.getY() + movePosition.getY();


    //remember previous position before we change it 
    Point prevPosition = position;
    
    // Move on X and Y axis independently
    if (canMoveToNewPos({ newX , position.getY() }) || ignoreObstacles)
    {
        position = { newX , position.getY() };
    }

    if (canMoveToNewPos({ position.getX(), newY }) || ignoreObstacles)
    {
        position = { position.getX(), newY };
    }

    if (useGravity)
    {
        gravity();
    }

    //check if the char the object stepped on previously wasnt an empty space 
    char charAtPrevPosition = gameBoard->getCharAtPos(prevPosition);
    if (charAtPrevPosition != ' ')
        // and draw it where we stepped on it
        draw(prevPosition ,charAtPrevPosition);

    draw();
}