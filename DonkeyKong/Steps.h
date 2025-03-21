#pragma once
#include <list>
#include <fstream>
#include "LevelFileException.h"
#include "utils.h"

class Steps
{
	long randomSeed = 0;
	// list of pairs: iteration id, step
	std::list<std::pair<size_t, std::pair<char, char>>> steps;
public:
	static Steps loadSteps(const std::string& filename);

	void saveSteps(const std::string& filename) const;
	
	long getRandomSeed() const 
	{
		return randomSeed;
	}
	
	void setRandomSeed(long seed) 
	{
		randomSeed = seed;
	}

	void addStep(size_t iteration, std::pair <char ,char> step)
	{
		steps.push_back({ iteration, step });
	}

	void clear()
	{
		steps.clear();
	}

	bool isNextStepOnIteration(size_t iteration) const 
	{
		return !steps.empty() && steps.front().first == iteration;
	}

	std::pair <char, char> popStep()
	{
		std::pair <char, char> step = steps.front().second;
		steps.pop_front();
		return step;
	}
};