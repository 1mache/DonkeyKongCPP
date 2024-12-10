#pragma once

#include <iostream>

#include "Board.h"
#include "Point.h"
#include "utils.h"

class Movement
{
    Point position;
    
    char spriteChar;
    
    Board* gameBoard = nullptr;
    
    // counts how many lines we fell, 0 if not in free fall 
    int fallHeight = 0;

    void draw(Point drawPosition, char c) const
    {
        gotoxy(drawPosition.getX(), drawPosition.getY());
        std::cout << c;
    }

    void gravity()
    {
        //pull down by 1
        Point newPosition = position.oneBelow();
        // every time gravity is successfully pulling our object we update fallHeight
        position = newPosition;
    }

public:

    Movement(Board* _gameBoard, char _spriteChar, Point _startPos): 
        gameBoard(_gameBoard), spriteChar(_spriteChar), position(_startPos) {}

    Point getPosition() const
    {
        return position;
    }

    void draw() const
    {
        draw(position , spriteChar);
    }

    void erase() const
    {
        draw(position , ' ');
    }
                                             //the move function can ignore obstacles, doesnt do it by default 
    void move(Point movePosition, bool useGravity, bool ignoreObstacles = false);

    bool canMoveToPos(Point newPos) const 
    { 
        return (!(gameBoard->isObstacleAtPos(newPos)) 
            && gameBoard->isPosInBounds(newPos)); 
    }

    bool checkOnGround() const
    {
        return !canMoveToPos(position.oneBelow());
    }

    int getFallHeight() { return fallHeight; }
};