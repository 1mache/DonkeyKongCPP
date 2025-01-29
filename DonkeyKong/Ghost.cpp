#include "Ghost.h"

bool Ghost::adjustDirection()
{
    bool changedDirection = false;

    // first handle direction change caused by environment (or random)
    if (reachedEndOfFloor() || reachedWall() || shouldRandomDirectionChange())
    {
        changeHorizontalDirection();
        changedDirection = true;
    }

    // then handle direction change caused by other regular ghosts
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