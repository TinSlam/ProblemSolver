#pragma once

#include "Problem.h"

class SlidingPuzzleSearchNode : public SearchNode{
private:
	int size = 3;
	int* tiles = nullptr;
	int emptyTilePosition = 0;

public:
	SlidingPuzzleSearchNode(int* tiles);
	~SlidingPuzzleSearchNode();
	bool isEqualTo(SearchNode* node);
	int* getTiles();
	int getEmptyTilePosition();
	int getSize();
};

class SlidingPuzzleAction : public Action{
public:
	enum Action{ UP, DOWN, RIGHT, LEFT };
	SlidingPuzzleAction(Action action, float cost);
	std::string toString();
	Action getAction();

private:
	Action action;
};

class SlidingPuzzleProblem : public Problem{
private :
	SlidingPuzzleAction* actionUp = nullptr;
	SlidingPuzzleAction* actionDown = nullptr;
	SlidingPuzzleAction* actionLeft = nullptr;
	SlidingPuzzleAction* actionRight = nullptr;
	SlidingPuzzleSearchNode* initialNode = nullptr;
	SlidingPuzzleSearchNode* goalNode = nullptr;
	std::list<SlidingPuzzleAction*> actions;

public :
	SlidingPuzzleProblem(int* tiles);
	~SlidingPuzzleProblem();

	SearchNode* getInitialNode();
	SearchNode* getGoalNode();
	Action* reverseAction(Action* action);
	bool isGoal(SearchNode* node);
	std::list<Action*>* getActions(SearchNode* node);
	SearchNode* getState(SearchNode* node, Action* action);
	float getHValue(SearchNode* node);
};