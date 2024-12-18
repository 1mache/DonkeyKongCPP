#pragma once

#include <iostream>

#include "Board.h"
#include "Point.h"
#include "utils.h"

// movement component of all the moving objects on screen
class Movement
{
    Point position;
    // char that represents the object on screen
    char spriteChar;
    
    Board* gameBoard = nullptr;
    
    // counts how many lines we fell, 0 if not in free fall 
    int fallHeight = 0;

    void draw(Point drawPosition, char c) const
    {
        if(gameBoard->isPosInBounds(drawPosition))
        {
            gotoScreenPos(drawPosition);
            std::cout << c;
        }
    }
    
    //pulls the object down one tile
    void gravity()
    {
        if(!checkOnGround())
        {
            position = position.oneBelow();
        }
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

    // moves the object and draws it in the new position 
    // the function can ignore obstacles, doesnt do it by default 
    void move(Point movePosition, bool useGravity, bool ignoreObstacles = false);

    bool canMoveToPos(Point newPos) const 
    {
        //returns true if the position is in bounds and there is no obstacle 
        return (!(gameBoard->isObstacleAtPos(newPos)) 
            && gameBoard->isPosInBounds(newPos)); 
    }

    bool checkOnGround() const
    {
        // in board we have certain objects that mario cant pass through
        // check if one of those is below us
        return !gameBoard->isObstacleAtPos(position.oneBelow());
    }

    int getFallHeight() 
    { 
        return fallHeight; 
    }
};