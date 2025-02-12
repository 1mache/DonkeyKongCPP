#pragma once
#include <list>
#include <fstream>
#include <sstream>
#include "LevelFileException.h"

class Results
{
public:
	static constexpr size_t NO_ITERATION = -1;
	enum ResultValue { LOST_LIFE, FINISHED, DIED, NO_RESULT };

	// utility function, translates result pair into a string
	static std::string resultToStr(std::pair<size_t, ResultValue> result);
private:
	std::list<std::pair<size_t, ResultValue>> results;
public:
	static Results loadResults(const std::string& filename);

	void saveResults(const std::string& filename) const;

	void addResult(size_t iteration, ResultValue result)
	{
		results.push_back({ iteration, result });
	}

	void clear()
	{
		results.clear();
	}

	bool hasResultOnIteration(size_t iteration) const
	{
		return (results.front().first == iteration);
	}

	std::pair<size_t, ResultValue> popResult();
};

