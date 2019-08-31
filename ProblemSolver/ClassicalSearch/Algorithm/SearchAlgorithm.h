#pragma once

#include "../Problem/Problem.h"
#include "../Utilities/SearchNode.h"

class SearchAlgorithm{
protected :
	std::list<Action*>* constructPath(SearchNode* node);

public :
	virtual std::list<Action*>* search(Problem* problem) = 0;
};