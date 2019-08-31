#include "AStarSearchAlgorithm.h"

std::list<Action*>* AStarSearchAlgorithm::search(Problem* problem){
	SearchNode* initialNode = problem->getInitialNode();
	initialNode->setFValue(0);

	if(problem->isGoal(initialNode)){
		return constructPath(nullptr);
	}

	openList.push(initialNode);

	while(!openList.isEmpty()){
		SearchNode* node = openList.pop();

		std::list<Action*>* actions = problem->getActions(node);
		for(auto it = actions->begin(); it != actions->end(); it++){
			SearchNode* child = problem->getState(node, *it);
			child->setAction(*it);
			child->setParent(node);
			if(problem->isGoal(child)){
				delete(actions);
				return constructPath(child);
			}

			child->setGValue(node->getGValue() + (*it)->getCost());
			child->setFValue(child->getGValue() + problem->getHValue(child));

			bool skip = false;
			auto openNode = openList.getNodes()->end();
			for(auto it = openList.getNodes()->begin(); it != openList.getNodes()->end(); it++){
				if(child->isEqualTo(*it)){
					openNode = it;
					if((*it)->getFValue() <= child->getFValue()) skip = true;
					break;
				}
			}

			if(skip){
				delete(child);
				continue;
			}
			skip = false;
			auto closedNode = closedList.end();
			for(auto it = closedList.begin(); it != closedList.end(); it++){
				if(child->isEqualTo(*it)){
					closedNode = it;
					if((*it)->getFValue() <= child->getFValue()) skip = true;
					break;
				}
			}

			if(skip)
				delete(child);
			else{
				if(openNode != openList.getNodes()->end()){
					openList.getNodes()->erase(openNode);
					openList.heapify(0);
				}
				if(closedNode != closedList.end()){
					closedList.erase(closedNode);
					closedList.push_back(child);
				}
				openList.push(child);
			}
		}
		delete(actions);
		closedList.push_back(node);
	}
	return nullptr;
}

bool AStarSearchAlgorithm::isInList(std::list<SearchNode*>* list, SearchNode* node){
	for(auto it = list->begin(); it != list->end(); it++){
		if(node->isEqualTo(*it) && (*it)->getFValue() <= node->getFValue()) return true;
	}
	return false;
}

bool AStarSearchAlgorithm::isInList(MinHeap* heap, SearchNode* node){
	std::vector<SearchNode*>* list = heap->getNodes();
	for(auto it = list->begin(); it != list->end(); it++){
		if((*it)->getFValue() > node->getFValue()) return false;
		if(node->isEqualTo(*it)) return true;
	}
	return false;
}