#include "Movement.h"

void Movement::move(int moveX, int moveY, bool useGravity)
{
    erase();

    /*int newX = position.x + direction.x;
    int newY = position.y + direction.y;*/

    int newX = position.x + moveX;
    int newY = position.y + moveY;

    // Move on X and Y axis independently
    if (canMoveToNewPos(newX, position.y))
    {
        setPosition(newX, position.y);
    }

    if (canMoveToNewPos(position.x, newY))
    {
        setPosition(position.x, newY);
    }

    if (useGravity)
    {
        gravity();
    }

    draw();
}