#pragma once

#include <list>
#include <map>
#include "SearchAlgorithm.h"

class BreadthFirstSearchAlgorithm : public SearchAlgorithm{
private :
	std::list<SearchNode*> openList;
	std::list<SearchNode*> closedList;
	bool isInList(std::list<SearchNode*>* list, SearchNode* node);

public :
	std::list<Action*>* search(Problem* problem);
};