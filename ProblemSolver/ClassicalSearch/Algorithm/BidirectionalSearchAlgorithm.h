#pragma once

#include <list>
#include "../Utilities/SearchNode.h"
#include "SearchAlgorithm.h"

class BidirectionalSearchAlgorithm : public SearchAlgorithm{
public :
	std::list<Action*>* search(Problem* problem);
	bool isInList(std::list<SearchNode*>* list, SearchNode* node);
	std::list<Action*>* constructPathFromLists(int i, SearchNode* node, std::list<SearchNode*>* list, std::list<SearchNode*>* reverse, Problem* problem);
};

