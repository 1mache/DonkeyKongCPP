#pragma once

#include <iostream>
#include "utils.h"

struct Point { int x, y; };
enum MoveState { UP, LEFT, DOWN, RIGHT, STAY };

class Movement
{
    static constexpr Point startPos = { 0, 0 };
    Point position = startPos;
    MoveState moveState = MoveState::STAY;
    char ch = '*';
    static constexpr Point directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
    Point direction = directions[STAY];

    void draw(char c) const
    {
        gotoxy(position.x, position.y);
        std::cout << c;
    }

public:
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
        direction = directions[state];
    }

    void setChar(char c)
    {
        ch = c;
    }

    void draw() const
    {
        draw(ch);
    }

    void erase()
    {
        draw(' ');
    }

    void move();
};