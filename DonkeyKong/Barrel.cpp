#include "Barrel.h"

void Barrel::setBarrelDirection()
{
    char charBelow = gameBoard->getCharAtPos(barrelMovement.getPosition().oneBelow());

    if (charBelow == LEFT_FLOOR)
    {
        barrelDir = RollDirection::LEFT;
    }
    else if (charBelow == RIGHT_FLOOR)
    {
        barrelDir = RollDirection::RIGHT;
    }
}

void Barrel::moveBarrel()
{
    gameBoard->resetCharAtPos(barrelMovement.getPosition());
    
    setBarrelDirection();
    barrelMovement.move(DIRECTIONS[barrelDir], true);

    gameBoard->updateBoardWithChar(barrelMovement.getPosition(), spriteChar);
}

// ===========================CHANGE??===========================
bool Barrel::checkExploded()
{
    if ((barrelMovement.getFallHeight() >= EXPLODE_FALL_HEIGHT) || (barrelMovement.reachedWall()))
    {
        barrelMovement.erase();

        return true;
    }

    return false;
}