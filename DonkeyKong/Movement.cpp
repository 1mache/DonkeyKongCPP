#include "Movement.h"

void Movement::move(int moveX, int moveY, bool useGravity, bool ignoreObstacles)
{
    //buffer holds the char that was at the object's previous position 
    static char buffer = ' ';
    static Point prevPosition;

    erase();

    //if buffer isnt empty
    if(buffer != ' ')
    {
        //draw whats in there and empty buffer
        draw(prevPosition, buffer);
        buffer = ' ';
    }
    
    int newX = position.x + moveX;
    int newY = position.y + moveY;

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

    // remember the char mario "stepped on" in the buffer variable
    char charOnBoard = gameBoard->getCharInPos(position.x, position.y);
    buffer = charOnBoard;
    prevPosition = position;


    draw();
}