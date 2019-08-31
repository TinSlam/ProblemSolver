#pragma once

#include <string>

class Action{
protected :
	float cost = 0;

public :
	virtual std::string toString() = 0;
	float getCost();
};

