#pragma once
#include <list>
#include <fstream>

class Results
{
public:
	enum ResultValue { tookAHit, finished, noResult };
private:
	std::list<std::pair<size_t, ResultValue>> results;
public:
	static Results loadResults(const std::string& filename);

	void saveResults(const std::string& filename) const;

	void addResult(size_t iteration, ResultValue result)
	{
		results.push_back({ iteration, result });
	}

	ResultValue popResult();

	bool isFinishedBy(size_t iteration) const
	{
		return results.empty() || results.back().first <= iteration;
	}
};

