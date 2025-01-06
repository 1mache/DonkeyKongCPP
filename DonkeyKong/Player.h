#pragma once

#include "Point.h"
#include "Movement.h"
#include "Constants.h"
#include "Game.h"

class Player : public Movement
{
    enum MoveState { UP, LEFT, DOWN, RIGHT, STAY };
    static constexpr Point DIRECTIONS[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
    static constexpr char KEYS[] = { 'w', 'a', 'x', 'd', 's' };
    static constexpr size_t NUM_KEYS = sizeof(KEYS) / sizeof(KEYS[0]);
    static constexpr char hammerKey = 'p';

    static constexpr int MAX_FALL_HEIGHT = 5;
    static constexpr int JUMP_HEIGHT = 2;
    static constexpr int DEATH_ANIMATION_FRAMES = 5;

    Game* curGame = nullptr;

    //movement component
    //Movement playerMovement;
    Board* gameBoard = nullptr;

    MoveState curState = STAY;
    //the player keeps the recent horizontal state regardless of the current state
    MoveState horizontalState = STAY;

    MoveState hammerDir = RIGHT;

    // tells if player has hammer
    bool hasHammer = false;

    //  mid jump not falling
    bool midJump = false;

    // height traveled during a jump 
    int heightTraveled = 0;

    // tells us if were climbing a ladder right now 
    bool midClimb = false;

    // the function is responsible for the first stage of the jump (until max jump height is reached) 
    // then mario just falls. (handled in movemnet by gravity function)  
    void jump();

    //checks if were trying to move sideways or pressed stay on ladder
    bool horizontalMovesOnLadder()
    {
        return (curState == STAY || curState == RIGHT || curState == LEFT) && midClimb;
    }

    bool isFalling() const
    {
        return getFallHeight() != 0;
    }

    bool canClimbUp(Point position) const;

    bool canClimbDown(Point position) const;

    void climbUp();

    void climbDown();

    void checkHammerPickup();

    void handleHammer();

    // change state by valid keyboard input (in KEYS[])
    void stateByKey(char key);

public:
    Player(Board* _gameBoard, char _spriteChar, Point _startPos, Game* _game) :
        Movement(_gameBoard, _spriteChar, _startPos), gameBoard(_gameBoard), curGame(_game) {}

    //Point getPosition()
    //{
    //    return getPosition();
    //}

    void movePlayer();

    void handleKeyboardInput(char key);

    bool checkFallDamage() const
    {
        //return true if we just fell more than MAX_FALL_HEIGHT tiles
        return (checkOnGround() && (getFallHeight() >= MAX_FALL_HEIGHT));
    }

    // checks collision with hazard objects 
    bool checkCollision() const
    {
        Point position = getPosition();
        return gameBoard->isHazardAtPos(position);
    }

    // actions when loses life
    void takeDamage();
};
