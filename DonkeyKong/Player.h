#pragma once

#include "Movement.h"

class Player
{
    Movement playerMovement;
    static constexpr char obsatcles[] = { '>', '<', '=' };
    static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

public:
    Player(Movement _movement): playerMovement(_movement)
    {}

    void stateByKey(char key);
    void movePlayer();
};
