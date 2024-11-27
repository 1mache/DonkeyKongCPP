#include <conio.h>
#include "Player.h"

void Player::stateByKey(char key)
{
    for (size_t i = 0; i < numKeys; i++) {
        if (std::tolower(key) == keys[i]) {
            playerMovement.setState((MoveState)i);
            return;
        }
    }
}

void Player::startPlayer(char ch, int x, int y)
{
    playerMovement.setChar(ch);
    playerMovement.setPosition(x, y);
    playerMovement.draw();
}

void Player::movePlayer()
{
    playerMovement.move();
}