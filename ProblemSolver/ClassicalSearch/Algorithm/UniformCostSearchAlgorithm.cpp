#include "UniformCostSearchAlgorithm.h"
#include "../Utilities/MinHeap.h"

std::list<Action*>* UniformCostSearchAlgorithm::search(Problem * problem){
	SearchNode* initialState = problem->getInitialNode();
	initialState->setFValue(0);

	MinHeap openList;
	openList.push(initialState);

	std::list<SearchNode*> closedList;

	while(!openList.isEmpty()){
		SearchNode* node = openList.pop();
		if(problem->isGoal(node)){
			return constructPath(node);
		}
		closedList.push_back(node);

		std::list<Action*>* actions = problem->getActions(node);
		for(auto it = actions->begin(); it != actions->end(); it++){
			SearchNode* child = problem->getState(node, *it);
			child->setParent(node);
			child->setAction(*it);
			child->setFValue(node->getFValue() + (*it)->getCost());

			bool skip = false;
			for(auto it = openList.getNodes()->begin(); it != openList.getNodes()->end(); it++){
				if(child->isEqualTo(*it)){
					if((*it)->getFValue() > child->getFValue()){
						(*it)->setFValue(child->getFValue());
						openList.heapify(0);
					}
					skip = true;
					break;
				}
			}
			if(skip){
				delete(child);
				continue;
			}

			for(auto it = closedList.begin(); it != closedList.end(); it++){
				if(child->isEqualTo(*it)){
					skip = true;
					break;
				}
			}
			if(skip){
				delete(child);
			}else{
				openList.push(child);
			}
		}
		delete(actions);
	}

	return nullptr;
}
