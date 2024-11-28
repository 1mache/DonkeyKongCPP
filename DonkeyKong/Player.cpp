#include <conio.h>
#include "MoveState.h"
#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < NUM_KEYS; i++) {
        if (std::tolower(key) == KEYS[i]) {
            playerMovement.setState((MoveState)i);
            return;
        }
    }
}

void Player::movePlayer()
{
    playerMovement.erase();
    playerMovement.move();
    playerMovement.draw();
}