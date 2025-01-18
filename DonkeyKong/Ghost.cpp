#include "Ghost.h"

bool Ghost::adjustDirection()
{
    if (reachedEndOfFloor() || reachedWall() || shouldRandomDirectionChange())
    {
        changeDirection();
        return true;
    }
    return false;
}

bool Ghost::reachedEndOfFloor() const
{
    Point positionToCheck;

    // check if the position of one char in front and below of the ghost direction doesn't contain a floor char 
    positionToCheck = (getPosition() + getDirection()).oneBelow();

    /*if (currentMoveDirection == MoveDirection::LEFT)
    {
        positionToCheck = getPosition().oneLeft().oneBelow();
    }

    else
    {
        positionToCheck = getPosition().oneRight().oneBelow();
    }*/

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
    gameBoard->updateBoardWithChar(getPosition(), Board::GHOST);
}