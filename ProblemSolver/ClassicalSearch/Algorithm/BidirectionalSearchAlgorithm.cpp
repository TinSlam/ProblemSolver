#include "BidirectionalSearchAlgorithm.h"

std::list<Action*>* BidirectionalSearchAlgorithm::search(Problem * problem){
	std::list<SearchNode*> openList;
	std::list<SearchNode*> openListReverse;
	std::list<SearchNode*> closedList;
	std::list<SearchNode*> closedListReverse;

	SearchNode* initialNode = problem->getInitialNode();
	SearchNode* goalNode = problem->getGoalNode();

	if(initialNode->isEqualTo(goalNode)){
		return constructPath(nullptr);
	}

	openList.push_front(initialNode);
	openListReverse.push_front(goalNode);

	while(!openList.empty() || !openListReverse.empty()){
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
				if(isInList(&openListReverse, child)){
					delete(actions);
					return constructPathFromLists(1, child, &openList, &openListReverse, problem);
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

		node = openListReverse.front();
		openListReverse.pop_front();
		closedListReverse.push_back(node);
		//std::cout << node->getDepth() << std::endl;
		actions = problem->getActions(node);
		for(auto it = actions->begin(); it != actions->end(); it++){
			SearchNode* child = problem->getState(node, *it);
			child->setAction(*it);
			child->setParent(node);
			//child->setDepth(node->getDepth() + 1);

			bool skip = false;
			auto openNode = openListReverse.end();
			for(auto it = openListReverse.begin(); it != openListReverse.end(); it++){
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

			auto closedNode = closedListReverse.end();
			for(auto it = closedListReverse.begin(); it != closedListReverse.end(); it++){
				if(child->isEqualTo(*it)){
					closedNode = it;
					if((*it)->getFValue() <= child->getFValue()) skip = true;
					break;
				}
			}
			if(skip){
				delete(child);
			}else{
				if(isInList(&openList, child)){
					delete(actions);
					return constructPathFromLists(2, child, &openList, &openListReverse, problem);
				}
				if(openNode != openListReverse.end()){
					openListReverse.erase(openNode);
				}
				if(closedNode != closedListReverse.end()){
					closedListReverse.erase(closedNode);
					closedListReverse.push_back(child);
				}
				openListReverse.push_back(child);
			}
		}
		delete(actions);
	}

	return nullptr;
}

bool BidirectionalSearchAlgorithm::isInList(std::list<SearchNode*>* list, SearchNode* node){
	for(auto it = list->begin(); it != list->end(); it++){
		if(node->isEqualTo(*it)) return true;
	}
	return false;
}

std::list<Action*>* BidirectionalSearchAlgorithm::constructPathFromLists(int i, SearchNode* searchNode, std::list<SearchNode*>* list, std::list<SearchNode*>* reverse, Problem* problem){
	SearchNode* node = nullptr;
	SearchNode* reverseNode = nullptr;
	switch(i){
		case 1 :
			node = searchNode;
			for(auto it = reverse->begin(); it != reverse->end(); it++){
				if((*it)->isEqualTo(searchNode)){
					reverseNode = *it;
					break;
				}
			}
			break;

		case 2 :
			reverseNode = searchNode;
			for(auto it = list->begin(); it != list->end(); it++){
				if((*it)->isEqualTo(searchNode)){
					node = *it;
					break;
				}
			}
			break;
	}
	std::list<Action*>* path = constructPath(node);
	std::list<Action*>* reversePath = constructPath(reverseNode);
	while(!reversePath->empty()){
		path->push_back(problem->reverseAction(reversePath->back()));
		reversePath->pop_back();
	}
	delete(reversePath);
	return path;
}
