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
    return false;
}

void Ghost::moveGhost()
{
    // remove ghost from board in its previous position
    gameBoard->resetCharAtPos(getPosition());

    setGhostDirection();
    move(DIRECTIONS[currentMoveDirection], false);
    // place ghost on board in its new position
    gameBoard->updateCurrentBoardWithChar(getPosition(), Board::GHOST);
}