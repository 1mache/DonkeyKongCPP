#include "Movement.h"

void Movement::move()
{
    position.x = position.x + direction.x;
    position.y = position.y + direction.y;
    // add function in board to check if position is in bounds or if there is an obsatcle
}