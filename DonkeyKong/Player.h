#pragma once

#include "Movement.h"

class Player
{
    Movement playerMovement;
    static constexpr char obsatcles[] = { '>', '<', '=' };
    char PlayerChar = '*';
    static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

public:
    void stateByKey(char key);
    void startPlayer(char ch, int x, int y);
    void movePlayer();
};
