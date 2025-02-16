#pragma once
#include "Event.h"

class PlayerEvent : public Event
{
public:
	enum class PlayerEventType { NOTHING = 0, LOST_A_LIFE, DIED, USED_HAMMER, WON };

	PlayerEvent(PlayerEventType _type = PlayerEventType::NOTHING) : type(_type) {}

	int getType() override
	{
		return static_cast<int>(type);
	}

private:
	PlayerEventType type;
};