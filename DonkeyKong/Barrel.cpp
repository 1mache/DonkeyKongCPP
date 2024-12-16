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

bool Barrel::reachedWall() const
{
    Point position = barrelMovement.getPosition();
    return(((!barrelMovement.canMoveToPos(position.oneLeft())) || (!barrelMovement.canMoveToPos(position.oneRight()))) 
        && barrelMovement.checkOnGround());
}

void Barrel::explode()
{
    barrelMovement.erase();
    gameBoard->resetCharAtPos(barrelMovement.getPosition());

    drawExplosion();
    eraseExplosion();
}

//void Barrel::drawExplosion()
//{
//    Point position = barrelMovement.getPosition();
//    int yPos = position.getY();
//    int xPos = position.getX();
//    for (int y = yPos - EXPLOSION_RADIUS; y <= yPos + EXPLOSION_RADIUS; y++)
//    {
//        for (int x = xPos - EXPLOSION_RADIUS; x <= xPos + EXPLOSION_RADIUS; x++)
//        {
//            Point curCharPos(x, y);
//
//            if (gameBoard->isPosInBounds(curCharPos))
//            {
//                gotoScreenPos(curCharPos);
//                std::cout << EXPLOSION_CHAR;
//                //Sleep(Constants::GAME_REFRESH_RATE / 10);
//                Sleep(1);
//            }
//        }
//    }
//}



void Barrel::drawExplosionPhase(int phase)
{
    Point position = barrelMovement.getPosition();
    int yPos = position.getY();
    int xPos = position.getX();
    
    Point cornerTL = position + Point(-phase, -phase);
    Point cornerTR = position + Point(phase, -phase);
    Point cornerBL = position + Point(-phase, phase);
    Point cornerBR = position + Point(phase, phase);

    Point curCharPos;
    for (int y = cornerTL.getY(); y <= cornerBL.getY(); y++)
    {
        for (int x = cornerTL.getX(); x <= cornerTR.getX(); x++)
        {
            curCharPos = { x,y };


            if ((y == cornerTL.getY() || y == cornerBL.getY()) ||
                (x == cornerTL.getX() || x == cornerTR.getX()))
            {
                if(gameBoard->isPosInBounds(curCharPos))
                {
                    gotoScreenPos(curCharPos);
                    std::cout << EXPLOSION_CHAR;
                }
            }
        }
    }
}

void Barrel::drawExplosion()
{
    for(int phase = 0; phase <= EXPLOSION_RADIUS; phase++)
    {
        drawExplosionPhase(phase);
        Sleep(Constants::GAME_REFRESH_RATE);
    }
}

void Barrel::eraseExplosion()
{
    Point position = barrelMovement.getPosition();
    int yPos = position.getY();
    int xPos = position.getX();
    for (int y = yPos - EXPLOSION_RADIUS; y <= yPos + EXPLOSION_RADIUS; y++)
    {
        for (int x = xPos - EXPLOSION_RADIUS; x <= xPos + EXPLOSION_RADIUS; x++)
        {
            Point curCharPos(x, y);

            if (gameBoard->isPosInBounds(curCharPos))
            {
                gotoScreenPos(curCharPos);
                std::cout << gameBoard->getCharAtPos(curCharPos);
                //Sleep(Constants::GAME_REFRESH_RATE / 10);
                //Sleep(1);
            }
        }
    }
}
