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
    
    char spriteChar;
    //Not used anymore  
    //MoveState moveState = MoveState::STAY;
    //Point direction = directions[(int)(MoveState::STAY)];

    Board* gameBoard = nullptr;

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
            position.y = newY;
        }
    }

public:

    Movement(Board* _gameBoard, char _spriteChar, Point _startPos): 
        gameBoard(_gameBoard), spriteChar(_spriteChar), position(_startPos) {}

    Point getPosition() const
    {
        return position;
    }
    // we have move
    //void setPosition(int x, int y)
    //{
    //    position.x = x;
    //    position.y = y;
    //}

    /*Point getDirection() const
    {
        return directions[(int)moveState];
    }

    //States are players / Barrels choice
    void setState(MoveState state)
    {
        moveState = state;
        direction = directions[(int)state];
    }

    MoveState getState() const
    {
        return moveState;
    }

    void setChar(char c)
    {
        spriteChar = c;
    }*/

    void draw() const
    {
        draw( position , spriteChar);
    }

    void erase()
    {
        draw(position , ' ');
    }
    
    void move(int x, int y, bool useGravity);

    bool canMoveToNewPos(int newX, int newY) const { return (!(gameBoard->isPosAnObstacle(newX, newY)) && gameBoard->isPosInBounds(newX, newY)); }
};