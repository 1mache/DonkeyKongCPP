#pragma once

#include <iostream>

#include "Board.h"
#include "Point.h"
#include "utils.h"
//Moved to player class
//static constexpr Point directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

class Movement
{
    Point position;
    
    //buffer holds the char that was at the object's previous position 
    char buffer = ' ';
    Point prevPosition;

    char spriteChar;
    
    Board* gameBoard = nullptr;
    //how many chars we fell
    int heightFell = 0;

    void draw(Point drawPosition, char c) const
    {
        gotoxy(drawPosition.x, drawPosition.y);
        std::cout << c;
    }

    void gravity()
    {
        //down by 1
        int newY = position.y + 1;

        if (canMoveToNewPos(position.x, newY))
        {
            //increment some freefallCount variable here 
            //to count how many tiles we fell 
            heightFell++;
            position.y = newY;
        }
        else
            heightFell = 0;
    }

public:

    Movement(Board* _gameBoard, char _spriteChar, Point _startPos): 
        gameBoard(_gameBoard), spriteChar(_spriteChar), position(_startPos), prevPosition(_startPos) {}

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
    void move(int x, int y, bool useGravity, bool ignoreObstacles = false);

    bool canMoveToNewPos(int newX, int newY) const 
    { 
        return (!(gameBoard->isPosAnObstacle(newX, newY)) 
            && gameBoard->isPosInBounds(newX, newY)); 
    }

    bool checkOnGround() const
    {
        return !canMoveToNewPos(position.x, position.y + 1);
    }
};