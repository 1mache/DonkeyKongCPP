#pragma once

#include <queue>
#include <memory>
#include "Event.h"

class EventQueue
{
	std::queue<std::unique_ptr<Event>> queue;
public:

	template<typename ActualEvent> // one of the derived classes
	void push(ActualEvent event)
	{
		// push the event to the queue while initializing it with its correct type
		queue.push(std::make_unique<ActualEvent>(event));
	}

	template<typename ActualEvent> // one of the derived classes 
	std::unique_ptr<ActualEvent> front() const
	{
		if (queue.empty())
			return nullptr;
		
		// try to cast the front into the desired type
		auto* casted = dynamic_cast<ActualEvent*>(queue.front().get());
		if (casted == nullptr)
			return nullptr; // failed to cast

		// create new unique ptr out of casted's content 
		return std::make_unique<ActualEvent>(*casted);
	}

	std::unique_ptr<Event> pop() 
	{
		if (queue.empty())
			return nullptr;

		std::unique_ptr<Event> returned = std::move(queue.front());
		queue.pop();

		return returned;
	}

	bool isEmpty() const
	{
		return queue.empty();
	}

	void makeEmpty();
};
