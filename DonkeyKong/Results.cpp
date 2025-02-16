#include "Results.h"

std::string Results::resultToStr(std::pair<size_t, ResultValue> result)
{
	std::ostringstream strStream;
	switch (result.second)
	{
	case LOST_LIFE:
		strStream << "Lost a life";
		break;

	case FINISHED:
		strStream << "Finished the level";
		break;

	case DIED:
		strStream << "Died";
		break;

	case NO_RESULT:
		strStream << "No result";
		break;
	
	default:
		break;
	}
	
	if(result.second != NO_RESULT)
		strStream << " on iteration " << result.first;

	return strStream.str();
}

Results Results::loadResults(const std::string& filename)
{
	std::ifstream results_file(filename);
	if(!results_file.is_open())
		throw LevelFileException("Error: couldn`t open file" + filename);

	Results results;
	size_t size;
	results_file >> size;
	
	while (!results_file.eof() && size != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
		
		size--;
	}
	return results;
}

void Results::saveResults(const std::string& filename) const 
{
	std::ofstream results_file(filename);
	if (!results_file.is_open())
		throw LevelFileException("Error: couldn`t open file" + filename);

	results_file << results.size();
	for (const auto& result : results) 
	{
		results_file << '\n' << result.first << ' ' << result.second;
	}

	results_file.close();
}

std::pair < size_t, Results::ResultValue > Results::popResult()
{
	if (results.empty())
		return { NO_ITERATION, Results::NO_RESULT };

	auto result = results.front();
	results.pop_front();
	return result;
}
