#include "Barrel.h"

void Barrel::setBarrelDirection()
{
    char charBelow = gameBoard->getCharAtPos(barrelMovement.getPosition().oneBelow());

    if (charBelow == LEFT_FLOOR)
    {
        rollDirection = RollDirection::LEFT;
    }
    else if (charBelow == RIGHT_FLOOR)
    {
        rollDirection = RollDirection::RIGHT;
    }
}

void Barrel::moveBarrel()
{
    gameBoard->resetCharAtPos(barrelMovement.getPosition());
    
    setBarrelDirection();
    barrelMovement.move(DIRECTIONS[rollDirection], true);

    gameBoard->updateBoardWithChar(barrelMovement.getPosition(), spriteChar);
}

bool Barrel::reachedWall() const
{
    Point position = barrelMovement.getPosition();
    return(((!barrelMovement.canMoveToPos(position.oneLeft())) || (!barrelMovement.canMoveToPos(position.oneRight()))) 
        && barrelMovement.checkOnGround());
}

// ===========================CHANGE NAME ??===========================
bool Barrel::checkExploded()
{
    // explode barrel if it reached the wall or fell more than x chars
    if (((barrelMovement.getFallHeight() >= EXPLODE_FALL_HEIGHT) && barrelMovement.checkOnGround()) 
        || reachedWall())
    {
        barrelMovement.erase();

        return true;
    }

    return false;
}