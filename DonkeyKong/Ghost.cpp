#include "Ghost.h"

bool Ghost::reachedEndOfFloor() const
{
    Point positionToCheck;

    if (currentMoveDirection == MoveDirection::LEFT)
    {
        positionToCheck = ghostMovement.getPosition().oneLeft().oneBelow();
    }

    else
    {
        positionToCheck = ghostMovement.getPosition().oneRight().oneBelow();
    }

    return(ghostMovement.canMoveToPos(positionToCheck));
}

bool Ghost::reachedAnotherGhost() const
{
    return false;
}

void Ghost::moveGhost()
{
    // remove ghost from board in its previous position
    gameBoard->resetCharAtPos(ghostMovement.getPosition());

    setGhostDirection();
    ghostMovement.move(DIRECTIONS[currentMoveDirection], false);
    // place ghost on board in its new position
    gameBoard->updateCurrentBoardWithChar(ghostMovement.getPosition(), Board::GHOST);
}