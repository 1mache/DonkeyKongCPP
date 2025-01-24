#pragma once
#include "Game.h"

class ReplayGame: public Game
{
	Game::KeyInput getInputKeys() const override;
	void setRandSeed() const override;
};