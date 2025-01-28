#pragma once

#include <iostream>
#include "Board.h"
#include "Point.h"
#include "utils.h"
#include <windows.h>

class MovingObject
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD color = (rand() % 8) + 1;

    Point position;
    // char that represents the object on screen
    char spriteChar;

    // counts how many lines we fell, 0 if not in free fall 
    int fallHeight = 0;

    void draw(Point drawPosition, char c) const
    {
        if(gameBoard->isPosInBounds(drawPosition))
        {
            SetConsoleTextAttribute(hConsole, color);
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

protected:
    // moves the object and draws it in the new position,
    // you can choose whether to apply gravity or not,
    // the function can ignore obstacles, doesnt do it by default 
    Board* gameBoard = nullptr;
    void move(Point moveDirection, bool useGravity, bool ignoreObstacles = false);

public:

    MovingObject(Board* _gameBoard, char _spriteChar, Point _startPos): 
        gameBoard(_gameBoard), spriteChar(_spriteChar), position(_startPos) {}

    virtual ~MovingObject() {};

    void draw() const
    {
        draw(position , spriteChar);
    }

    void erase() const
    {
        draw(position , Board::BLANK_SPACE);
    }

    Point getPosition() const
    {
        return position;
    }

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
        return gameBoard->isObstacleAtPos(position.oneBelow());
    }

    int getFallHeight() const 
    { 
        return fallHeight; 
    }
    
    // function that the every object overrides and is used for the object to update itself in the current frame
    // its position, certain states, etc.
    virtual void update() = 0;
};