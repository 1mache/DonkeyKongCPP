#pragma once

#include "Movement.h"

class Player
{
    Movement playerMovement;
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);

public:
    Player(Movement _movement): playerMovement(_movement)
    {}

    void stateByKey(char key);
    void movePlayer();
};
