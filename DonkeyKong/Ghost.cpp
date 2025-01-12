#include "Ghost.h"

bool Ghost::reachedEndOfFloor() const
{
    Point positionToCheck;

    if (currentMoveDirection == MoveDirection::LEFT)
    {
        positionToCheck = getPosition().oneLeft().oneBelow();
    }

    else
    {
        positionToCheck = getPosition().oneRight().oneBelow();
    }

    return(canMoveToPos(positionToCheck));
}

bool Ghost::reachedAnotherGhost() const
{
    Point checkPos = getPosition() + DIRECTIONS[currentMoveDirection];
    return gameBoard->isGhostAtPos(checkPos);
}

void Ghost::moveGhost()
{
    // remove ghost from board in its previous position
    gameBoard->resetCharAtPos(getPosition());

    MoveDirection prevDirection = currentMoveDirection;
    
    setGhostDirection();

    // if we changed direction this turn, dont move
    if(currentMoveDirection != prevDirection)
    {
        move(Constants::POINT_ZERO, false);
    }
    else
    {
        move(DIRECTIONS[currentMoveDirection], false);
    }

    // place ghost on board in its new position
    gameBoard->updateBoardWithChar(getPosition(), Board::GHOST);
}