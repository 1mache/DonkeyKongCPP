#pragma once

class Event
{
public:
	virtual ~Event() = default;
	virtual int getType() const = 0;
};
