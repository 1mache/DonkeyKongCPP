#pragma once

#include <iostream>

#include "Board.h"
#include "MoveState.h"
#include "utils.h"

struct Point { int x, y; };
class Movement
{
    static constexpr Point directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };

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

public:

    Movement(Board* _gameBoard, char _spriteChar, Point startPos): gameBoard(_gameBoard), spriteChar(_spriteChar), position(startPos){}

    Point getPosition()
    {
        return position;
    }

    void setPosition(int x, int y)
    {
        position.x = x;
        position.y = y;
    }

    void setState(MoveState state)
    {
        moveState = state;
        direction = directions[(int)state];
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

    void move();
};