#pragma once

#include <list>
#include "SearchAlgorithm.h"
#include "../Utilities/MinHeap.h"

class AStarSearchAlgorithm : public SearchAlgorithm{
private:
	MinHeap openList;
	std::list<SearchNode*> closedList;
	bool isInList(std::list<SearchNode*>* map, SearchNode* node);
	bool isInList(MinHeap* list, SearchNode* node);

public:
	std::list<Action*>* search(Problem* problem);
};

