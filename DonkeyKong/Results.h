#pragma once
#include <list>
#include <fstream>

class Results
{
public:
	static constexpr size_t NO_ITERATION = -1;
	enum ResultValue { LOST_LIFE, FINISHED, DIED, NO_RESULT };
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

	std::pair<size_t, ResultValue> popResult();
};

