#include "Steps.h"

Steps Steps::loadSteps(const std::string& filename) 
{
	Steps steps;
	std::ifstream steps_file(filename);
	if(!steps_file.is_open()){}
		//TODO: throw exception

	steps_file >> steps.randomSeed;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size != 0) {
		size_t iteration;
		std::pair <char, char> step;
		steps_file >> iteration >> step.first >> step.second;
		steps.addStep(iteration, step);
		
		size--;
	}
	steps_file.close();
	return steps;
}

void Steps::saveSteps(const std::string& filename) const 
{
	std::ofstream steps_file(filename);
	if (!steps_file.is_open()){}
		//TODO: throw exception

	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& stepPair : steps) {
		const auto step = stepPair.second;
		steps_file << '\n' << stepPair.first << ' ' << step.first << step.second;
	}
	steps_file.close();
}
