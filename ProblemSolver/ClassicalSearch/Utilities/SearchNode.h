#pragma once

#include "Action.h"

class SearchNode{
private :
	SearchNode* parent = nullptr;
	Action* action = nullptr;
	float fValue = 0;
	float gValue = 0;
	int depth = 0;

public :
	virtual bool isEqualTo(SearchNode* node) = 0;
	void setParent(SearchNode* parent);
	SearchNode* getParent();
	void setAction(Action* action);
	Action* getAction();
	void setFValue(float fValue);
	void setGValue(float gValue);
	void setDepth(int depth);
	float getFValue();
	float getGValue();
	int getDepth();
};