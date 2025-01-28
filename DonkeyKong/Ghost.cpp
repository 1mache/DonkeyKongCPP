#include "Ghost.h"

bool Ghost::adjustDirection()
{
    bool changedDirection = false;

    if (reachedEndOfFloor() || reachedWall() || shouldRandomDirectionChange())
    {
        changeHorizontalDirection();
        changedDirection = true;
    }

    if (reachedAnotherGhost())
    {
        changeHorizontalDirection();
        changedDirection = true;
    }

    return changedDirection;
}

bool Ghost::reachedEndOfFloor() const
{
    Point positionToCheck;

    // check if the position of one char in front and below of the ghost direction doesn't contain a floor char 
    positionToCheck = (getPosition() + getDirection()).oneBelow();

    return(canMoveToPos(positionToCheck));
}

void Ghost::moveGhost()
{
    // remove ghost from board in its previous position
    gameBoard->resetCharAtPos(getPosition());

    // if we changed direction this turn, don't move
    if(!adjustDirection())
    {
        move(DIRECTIONS[currentMoveDirection], false);
    }

    // place ghost on board in its new position
    gameBoard->updateBoardWithChar(getPosition(), ghostChar);
}

bool Ghost::reachedAnotherGhost() const
{
    return (gameBoard->isGhostAtPos(getPosition() + DIRECTIONS[currentMoveDirection]));
    //// check if another ghost is next to this ghost: xx 
    //Point checkPos = getPosition() + DIRECTIONS[currentMoveDirection];
    //if (gameBoard->isGhostAtPos(checkPos))
    //{
    //    return true;
    //}

    //// check if another ghost is 2 chars next to this ghost but in its direction: -> x x <- 
    //checkPos = checkPos + DIRECTIONS[currentMoveDirection];
    //if (gameBoard->isGhostAtPos(checkPos))
    //{
    //    if (getDirection() + ghostsManager->findGhostByPosition(checkPos)->getDirection() == Constants::POINT_ZERO)
    //    {
    //        return true;
    //    }
    //}

    //return false;
}