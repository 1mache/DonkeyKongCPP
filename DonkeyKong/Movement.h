#pragma once

#include <iostream>

#include "Board.h"
#include "MoveState.h"
#include "utils.h"

struct Point { int x, y; };
static constexpr Point directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

class Movement
{
    char spriteChar;
    
    Point position;
    MoveState moveState = MoveState::STAY;
    Point direction = directions[(int)(MoveState::STAY)];

    Board* gameBoard = nullptr;

    void draw(char c) const
    {
        gotoxy(position.x, position.y);
        std::cout << c;
    }

    void gravity()
    {
        int newY = position.y + directions[(int)(MoveState::DOWN)].y;

        if (canMoveToNewPos(position.x, newY))
        {
            position.y = newY;
        }
    }

public:

    Movement(Board* _gameBoard, char _spriteChar, Point startPos): gameBoard(_gameBoard), spriteChar(_spriteChar), position(startPos){}

    Point getPosition() const
    {
        return position;
    }

    void setPosition(int x, int y)
    {
        position.x = x;
        position.y = y;
    }

    Point getDirection() const
    {
        return directions[(int)moveState];
    }

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
    }

    void draw() const
    {
        draw(spriteChar);
    }

    void erase()
    {
        draw(' ');
    }

    void move(int x, int y, bool useGravity);

    bool canMoveToNewPos(int newX, int newY) const { return ((gameBoard->isPosAnObstacle(newX, newY) == false) && gameBoard->isPosInBounds(newX, newY) == true); }
    bool reachedWall() const { return gameBoard->isPosNearWall(position.x, position.y); }
};