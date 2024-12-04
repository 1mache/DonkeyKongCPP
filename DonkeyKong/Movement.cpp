#include "Movement.h"

void Movement::move(int moveX, int moveY, bool useGravity, bool ignoreObstacles)
{
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
    buffer = gameBoard->getCharInPos(position.x, position.y);
    prevPosition = position;


    draw();
}