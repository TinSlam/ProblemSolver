#pragma once

#include <list>
#include "SearchAlgorithm.h"

class DepthFirstSearchAlgorithm : public SearchAlgorithm{
private:
	std::list<SearchNode*> openList;
	std::list<SearchNode*> closedList;

public:
	std::list<Action*>* search(Problem* problem);
	std::list<Action*>* limitedDepth(Problem* problem, int depth);
	std::list<Action*>* iterativeSearch(Problem* problem);
};

