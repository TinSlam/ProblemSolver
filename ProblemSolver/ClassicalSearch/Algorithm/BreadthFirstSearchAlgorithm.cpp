#include "BreadthFirstSearchAlgorithm.h"

std::list<Action*>* BreadthFirstSearchAlgorithm::search(Problem* problem){
	SearchNode* initialNode = problem->getInitialNode();

	//initialNode->setDepth(1);

	if(problem->isGoal(initialNode)){
		return constructPath(nullptr);
	}

	openList.push_back(initialNode);
	
	while(!openList.empty()){
		SearchNode* node = openList.front();
		openList.pop_front();
		closedList.push_back(node);
		//std::cout << node->getDepth() << std::endl;
		std::list<Action*>* actions = problem->getActions(node);
		for(auto it = actions->begin(); it != actions->end(); it++){
			SearchNode* child = problem->getState(node, *it);
			child->setAction(*it);
			child->setParent(node);
			//child->setDepth(node->getDepth() + 1);

			bool skip = false;
			auto openNode = openList.end();
			for(auto it = openList.begin(); it != openList.end(); it++){
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

			auto closedNode = closedList.end();
			for(auto it = closedList.begin(); it != closedList.end(); it++){
				if(child->isEqualTo(*it)){
					closedNode = it;
					if((*it)->getFValue() <= child->getFValue()) skip = true;
					break;
				}
			}
			if(skip){
				delete(child);
			}else{
				if(problem->isGoal(child)){
					delete(actions);
					return constructPath(child);
				}
				if(openNode != openList.end()){
					openList.erase(openNode);
				}
				if(closedNode != closedList.end()){
					closedList.erase(closedNode);
					closedList.push_back(child);
				}
				openList.push_back(child);
			}
		}
		delete(actions);
	}
	return nullptr;
}

bool BreadthFirstSearchAlgorithm::isInList(std::list<SearchNode*>* list, SearchNode* node){
	for(auto it = list->begin(); it != list->end(); it++){
		if(node->isEqualTo(*it)) return true;
	}
	return false;
}