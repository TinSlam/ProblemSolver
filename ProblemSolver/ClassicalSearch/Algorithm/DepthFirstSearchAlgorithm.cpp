#include "DepthFirstSearchAlgorithm.h"

std::list<Action*>* DepthFirstSearchAlgorithm::search(Problem * problem){
	SearchNode* initialNode = problem->getInitialNode();

	if(problem->isGoal(initialNode)){
		return constructPath(nullptr);
	}

	openList.push_back(initialNode);

	while(!openList.empty()){
		SearchNode* node = openList.back();
		openList.pop_back();
		closedList.push_back(node);
		std::list<Action*>* actions = problem->getActions(node);
		for(auto it = actions->begin(); it != actions->end(); it++){
			SearchNode* child = problem->getState(node, *it);
			child->setAction(*it);
			child->setParent(node);

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
			}
			else{
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
		//std::cout << openList.size() << " " << closedList.size() << std::endl;
		delete(actions);
	}
	return nullptr;
}

std::list<Action*>* DepthFirstSearchAlgorithm::limitedDepth(Problem * problem, int depth){
	SearchNode* initialNode = problem->getInitialNode();
	initialNode->setDepth(1);

	if(problem->isGoal(initialNode)){
		return constructPath(nullptr);
	}

	openList.push_back(initialNode);

	while(!openList.empty()){
		SearchNode* node = openList.back();
		openList.pop_back();
		closedList.push_back(node);
		if(node->getDepth() >= depth){
			continue;
		}
		std::list<Action*>* actions = problem->getActions(node);
		for(auto it = actions->begin(); it != actions->end(); it++){
			SearchNode* child = problem->getState(node, *it);
			child->setAction(*it);
			child->setParent(node);
			child->setDepth(node->getDepth() + 1);

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
			}
			else{
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

	for(auto it = openList.begin(); it != openList.end(); it++){
		if(*it == initialNode){
			continue;
		}
		delete(*it);
	}
	for(auto it = closedList.begin(); it != closedList.end(); it++){
		if(*it == initialNode){
			continue;
		}
		delete(*it);
	}
	openList.clear();
	closedList.clear();

	return nullptr;
}

std::list<Action*>* DepthFirstSearchAlgorithm::iterativeSearch(Problem * problem){
	int depth = 1;
	std::list<Action*>* path = nullptr;
	while(path == nullptr){
		printf("Current depth : %d.\n", depth);
		path = limitedDepth(problem, depth++);
	}
	return path;
}