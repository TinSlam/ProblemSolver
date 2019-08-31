#include "SearchAlgorithm.h"

std::list<Action*>* SearchAlgorithm::constructPath(SearchNode* node){
	std::list<Action*>* path = new std::list<Action*>();

	if(node != nullptr){
		while(node->getParent() != nullptr){
			path->push_front(node->getAction());
			SearchNode* temp = node->getParent();
			delete(node);
			node = temp;
		}
	}

	return path;
}