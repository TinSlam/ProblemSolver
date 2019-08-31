#include "SlidingPuzzleProblem.h"

SlidingPuzzleProblem::SlidingPuzzleProblem(int* tiles){
	actionUp = new SlidingPuzzleAction(SlidingPuzzleAction::UP, 1);
	actionDown = new SlidingPuzzleAction(SlidingPuzzleAction::DOWN, 1);
	actionRight = new SlidingPuzzleAction(SlidingPuzzleAction::RIGHT, 1);
	actionLeft = new SlidingPuzzleAction(SlidingPuzzleAction::LEFT, 1);
	actions.push_back(actionUp);
	actions.push_back(actionDown);
	actions.push_back(actionRight);
	actions.push_back(actionLeft);
	initialNode = new SlidingPuzzleSearchNode(tiles);
	goalNode = new SlidingPuzzleSearchNode(new int[9]{1, 2, 3, 4, 5, 6, 7, 8, 9});
}

SlidingPuzzleProblem::~SlidingPuzzleProblem(){
	for(auto it = actions.begin(); it != actions.end(); it++){
		delete(*it);
	}
	delete(initialNode);
	delete(goalNode);
}

SearchNode* SlidingPuzzleProblem::getInitialNode(){
	return initialNode;
}

SearchNode* SlidingPuzzleProblem::getGoalNode(){
	return goalNode;
}

Action * SlidingPuzzleProblem::reverseAction(Action* actionG){
	SlidingPuzzleAction* action = (SlidingPuzzleAction*) actionG;
	switch(action->getAction()){
		case SlidingPuzzleAction::Action::UP :
			return actionDown;

		case SlidingPuzzleAction::Action::DOWN :
			return actionUp;

		case SlidingPuzzleAction::Action::RIGHT :
			return actionLeft;

		case SlidingPuzzleAction::Action::LEFT :
			return actionRight;
	}
	return nullptr;
}

bool SlidingPuzzleProblem::isGoal(SearchNode* searchNode){
	SlidingPuzzleSearchNode* node = (SlidingPuzzleSearchNode*) searchNode;
	int size = node->getSize();
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(node->getTiles()[i * size + j] != i * size + j + 1) return false;
		}
	}
	return true;
}

std::list<Action*>* SlidingPuzzleProblem::getActions(SearchNode* searchNode){
	SlidingPuzzleSearchNode* node = (SlidingPuzzleSearchNode*) searchNode;
	std::list<Action*>* list = new std::list<Action*>();

	int index = node->getEmptyTilePosition();
	int size = node->getSize();

	for(auto it = actions.begin(); it != actions.end(); it++){
		switch((*it)->getAction()){
			case SlidingPuzzleAction::Action::UP :
				if(index >= size) list->push_back(*it);
				break;

			case SlidingPuzzleAction::Action::DOWN :
				if(index < size * (size - 1)) list->push_back(*it);
				break;

			case SlidingPuzzleAction::Action::LEFT :
				if(index % size != 0) list->push_back(*it);
				break;

			case SlidingPuzzleAction::Action::RIGHT :
				if(index % size != size - 1) list->push_back(*it);
				break;
		}
	}

	return list;
}

SearchNode* SlidingPuzzleProblem::getState(SearchNode* searchNode, Action* actionG){
	SlidingPuzzleSearchNode* node = (SlidingPuzzleSearchNode*) searchNode;
	SlidingPuzzleAction* action = (SlidingPuzzleAction*) actionG;

	int* tiles = node->getTiles();
	int index = node->getEmptyTilePosition();
	int size = node->getSize();

	int* newTiles = new int[size * size];
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			newTiles[i * size + j] = tiles[i * size + j];
		}
	}

	switch(action->getAction()){
		case SlidingPuzzleAction::Action::UP :
			newTiles[index] = tiles[index - size];
			newTiles[index - size] = size * size;
			break;

		case SlidingPuzzleAction::Action::DOWN :
			newTiles[index] = tiles[index + size];
			newTiles[index + size] = size * size;
			break;

		case SlidingPuzzleAction::Action::RIGHT :
			newTiles[index] = tiles[index + 1];
			newTiles[index + 1] = size * size;
			break;

		case SlidingPuzzleAction::Action::LEFT :
			newTiles[index] = tiles[index - 1];
			newTiles[index - 1] = size * size;
			break;
	}

	return new SlidingPuzzleSearchNode(newTiles);
}

float SlidingPuzzleProblem::getHValue(SearchNode* searchNode){
	SlidingPuzzleSearchNode* node = (SlidingPuzzleSearchNode*)searchNode;
	int size = node->getSize();
	float value = 0;
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			int num = node->getTiles()[i * 3 + j] - 1;
			value += abs(i - num / 3) + abs(j - num % 3);
		}
	}
	return value;
}

SlidingPuzzleSearchNode::SlidingPuzzleSearchNode(int* tiles){
	this->tiles = tiles;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(tiles[i * size + j] == size * size){
				emptyTilePosition = i * size + j;
				return;
			}
		}
	}
}

SlidingPuzzleSearchNode::~SlidingPuzzleSearchNode(){
	delete(tiles);
}

bool SlidingPuzzleSearchNode::isEqualTo(SearchNode* searchNode){
	SlidingPuzzleSearchNode* node = (SlidingPuzzleSearchNode*) searchNode;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(tiles[i * size + j] != node->getTiles()[i * size + j]) return false;
		}
	}
	return true;
}

int* SlidingPuzzleSearchNode::getTiles(){
	return tiles;
}

int SlidingPuzzleSearchNode::getEmptyTilePosition(){
	return emptyTilePosition;
}

int SlidingPuzzleSearchNode::getSize(){
	return size;
}

SlidingPuzzleAction::SlidingPuzzleAction(Action action, float cost){
	this->action = action;
	this->cost = cost;
}

std::string SlidingPuzzleAction::toString(){
	switch(action){
		case UP :
			return "Up";

		case DOWN :
			return "Down";

		case RIGHT :
			return "Right";

		case LEFT :
			return "Left";
			
		default : 
			return "";
	}
}

SlidingPuzzleAction::Action SlidingPuzzleAction::getAction(){
	return action;
}
