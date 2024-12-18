#include "Barrel.h"

void Barrel::setBarrelDirection()
{
    char charBelow = gameBoard->getCharAtPos(barrelMovement.getPosition().oneBelow());

    if (charBelow == LEFT_FLOOR)
    {
        rollDirection = DIRECTIONS[RollDirection::LEFT];
    }
    else if (charBelow == RIGHT_FLOOR)
    {
        rollDirection = DIRECTIONS[RollDirection::RIGHT];
    }
}

void Barrel::moveBarrel()
{
    gameBoard->resetCharAtPos(barrelMovement.getPosition());
    
    setBarrelDirection();
    barrelMovement.move(rollDirection, true);

    gameBoard->updateBoardWithChar(barrelMovement.getPosition(), spriteChar);
}

void Barrel::explode()
{
    barrelMovement.erase();
    gameBoard->resetCharAtPos(barrelMovement.getPosition());

    drawExplosionPhase();
}

void Barrel::drawExplosionPhase()
{
    Point position = barrelMovement.getPosition();
    int yPos = position.getY();
    int xPos = position.getX();
    
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
                //only print the explosion at certain position if it is in bounds and there isnt an obstacle(looks better)
                if(gameBoard->isPosInBounds(curCharPos) && !gameBoard->isObstacleAtPos(curCharPos))
                {
                    gotoScreenPos(curCharPos);
                    gameBoard->updateBoardWithChar(curCharPos ,EXPLOSION_CHAR);
                    std::cout << EXPLOSION_CHAR;
                }
            }
        }
    }

    explosionPhase++;
}

void Barrel::eraseExplosion()
{
    Point position = barrelMovement.getPosition();
    // top left and bottom right corners
    Point cornerTL = position + Point(-EXPLOSION_RADIUS, -EXPLOSION_RADIUS);
    Point cornerBR = position + Point(EXPLOSION_RADIUS, EXPLOSION_RADIUS);

    Point curCharPos;

    for (int y = cornerTL.getY(); y <= cornerBR.getY(); y++)
    {
        for (int x = cornerTL.getX(); x <= cornerBR.getX(); x++)
        {
            Point curCharPos(x, y);

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
    if (exploded())
    {
        eraseExplosion();
    }
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