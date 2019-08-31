#pragma once

#include <list>
#include "SearchAlgorithm.h"

class UniformCostSearchAlgorithm : public SearchAlgorithm{
public:
	std::list<Action*>* search(Problem* problem);
};