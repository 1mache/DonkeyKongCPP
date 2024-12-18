#include "Movement.h"

void Movement::move(Point moveDirection, bool useGravity, bool ignoreObstacles)
{
    erase();

    //add direction to current position in each axis
    int newX = position.getX() + moveDirection.getX();
    int newY = position.getY() + moveDirection.getY();


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
    
    // update fallHeight based on if gravity pulls us
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