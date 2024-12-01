#include "Movement.h"

void Movement::move(int moveX, int moveY, bool useGravity)
{
    erase();

    int newX = position.x + moveX;
    int newY = position.y + moveY;

    // Move on X and Y axis independently
    if (canMoveToNewPos(newX, position.y))
    {
        position = { newX, position.y };
    }

    if (canMoveToNewPos(position.x, newY))
    {
        position = { position.x, newY };
    }

    if (useGravity)
    {
        gravity();
    }

    draw();
}