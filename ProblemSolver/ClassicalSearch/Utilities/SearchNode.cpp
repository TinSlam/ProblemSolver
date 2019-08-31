#include "SearchNode.h"

void SearchNode::setParent(SearchNode* parent){
	this->parent = parent;
}

SearchNode* SearchNode::getParent(){
	return parent;
}

void SearchNode::setAction(Action* action){
	this->action = action;
}

Action* SearchNode::getAction(){
	return action;
}

void SearchNode::setFValue(float fValue){
	this->fValue = fValue;
}

void SearchNode::setGValue(float gValue){
	this->gValue = gValue;
}

void SearchNode::setDepth(int depth){
	this->depth = depth;
}

float SearchNode::getFValue(){
	return fValue;
}

float SearchNode::getGValue(){
	return gValue;
}

int SearchNode::getDepth(){
	return depth;
}
