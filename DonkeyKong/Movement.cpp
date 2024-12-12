#include "Movement.h"

void Movement::move(Point movePosition, bool useGravity, bool ignoreObstacles)
{
    erase();

    int newX = position.getX() + movePosition.getX();
    int newY = position.getY() + movePosition.getY();


    //remember previous position before we change it 
    Point prevPosition = position;
    
    // Move on X and Y axis independently:
    // (the new position on both x and y axis has to be in bounds,
    // and cannot be an obstacle if the ignoreObstacles flag is off)
     
    // new X, same Y
    Point newXPosition = { newX , position.getY() };
    if (canMoveToPos(newXPosition) || 
        (ignoreObstacles && gameBoard->isPosInBounds(newXPosition)))
    {
        position = newXPosition;
    }

    // same X, new Y
    Point newYPosition = { position.getX(), newY };
    if (canMoveToPos(newYPosition) ||
        (ignoreObstacles && gameBoard->isPosInBounds(newYPosition)))
    {
        position = { position.getX(), newY };
    }

    if (!checkOnGround() && useGravity)
    {
        gravity();
        fallHeight++;
    }
    else
    {
        fallHeight = 0;
    }

    //check if the char the object stepped on previously wasnt an empty space 
    char charAtPrevPosition = gameBoard->getCharAtPos(prevPosition);
    if (charAtPrevPosition != ' ')
        // and draw it where we stepped on it
        draw(prevPosition ,charAtPrevPosition);

    draw();
}

// move to barrel class
bool Movement::reachedWall() const
{
    return(((!canMoveToPos(position.oneLeft())) || (!canMoveToPos(position.oneRight()))) && checkOnGround());
}