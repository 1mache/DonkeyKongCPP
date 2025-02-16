#include "EventQueue.h"

void EventQueue::makeEmpty()
{
	while (!queue.empty())
		queue.pop();
}
