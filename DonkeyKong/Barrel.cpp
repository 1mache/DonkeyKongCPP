#include "Barrel.h"

void Barrel::setBarrelDirection()
{
    char charBelow = gameBoard->getCharAtPos(barrelMovement.getPosition().oneBelow());

    //set direction based on floor
    if (charBelow == LEFT_FLOOR)
    {
        currentRollDirection = RollDirection::LEFT;
    }
    else if (charBelow == RIGHT_FLOOR)
    {
        currentRollDirection = RollDirection::RIGHT;
    }
}

void Barrel::moveBarrel()
{
    // remove barrel from board in its previous position
    gameBoard->resetCharAtPos(barrelMovement.getPosition());
    
    setBarrelDirection();
    barrelMovement.move(DIRECTIONS[currentRollDirection], true);
    // place barrel on board in its new position
    gameBoard->updateCurrentBoardWithChar(barrelMovement.getPosition(), Board::BARREL);
}

void Barrel::explode()
{
    // erase barrel from screen
    barrelMovement.erase();
    // remove it from board
    gameBoard->resetCharAtPos(barrelMovement.getPosition());

    //start the explosion cycle
    drawExplosionPhase();
}

void Barrel::drawExplosionPhase()
{
    Point position = barrelMovement.getPosition();
    
    //topLeft and bottomRight corners of the explosion "rings"
    Point cornerTL = position + Point(-explosionPhase, -explosionPhase);
    Point cornerBR = position + Point(explosionPhase, explosionPhase);

    Point curCharPos;
    for (int y = cornerTL.getY(); y <= cornerBR.getY(); y++)
    {
        for (int x = cornerTL.getX(); x <= cornerBR.getX(); x++)
        {
            curCharPos = { x,y };

            if ((y == cornerTL.getY() || y == cornerBR.getY()) ||
                (x == cornerTL.getX() || x == cornerBR.getX()))
            {
                //only print the explosion at certain position if it is in bounds and there isnt an obstacle
                if(gameBoard->isPosInBounds(curCharPos) && !gameBoard->isObstacleAtPos(curCharPos))
                {
                    gotoScreenPos(curCharPos);
                    gameBoard->updateCurrentBoardWithChar(curCharPos ,Board::EXPLOSION);
                    std::cout << Board::EXPLOSION;
                }
            }
        }
    }

    //make the explosion radius larger
    explosionPhase++;
}

void Barrel::eraseExplosion()
{
    Point position = barrelMovement.getPosition();
    // top left and bottom right corners
    Point cornerTL = position + Point(-EXPLOSION_RADIUS, -EXPLOSION_RADIUS);
    Point cornerBR = position + Point(EXPLOSION_RADIUS, EXPLOSION_RADIUS);

    Point curCharPos;

    // erase the explosion from screen and from board, we can do it in a regular fashion 
    // and not in phases because this is not animated, and happens between frames
    for (int y = cornerTL.getY(); y <= cornerBR.getY(); y++)
    {
        for (int x = cornerTL.getX(); x <= cornerBR.getX(); x++)
        {
            curCharPos = { x, y };

            if (gameBoard->isPosInBounds(curCharPos))
            {
                gotoScreenPos(curCharPos);
                gameBoard->resetCharAtPos(curCharPos);
                std::cout << gameBoard->getCharAtPos(curCharPos);
            }
        }
    }
}

void Barrel::update()
{
    // this is the final point in the life of a barrel
    if (exploded())
    {
        eraseExplosion();
    }
    // if were in the middle of an explosion just continue the explosion
    else if (explosionPhase > 0)
    {
        drawExplosionPhase();
    }
    else if (needsToExplode())
    {
        explode();
    }
    else
    {
        moveBarrel();
    }
}