#pragma once

#include <list>
#include "../Utilities/SearchNode.h"
#include "../Utilities/Action.h"

class Problem{
public :
	virtual SearchNode* getInitialNode() = 0;
	virtual SearchNode* getGoalNode() = 0;
	virtual Action* reverseAction(Action* action) = 0;
	virtual std::list<Action*>* getActions(SearchNode* node) = 0;
	virtual bool isGoal(SearchNode* node) = 0;
	virtual SearchNode* getState(SearchNode* node, Action* action) = 0;
	virtual float getHValue(SearchNode* node) = 0;
};