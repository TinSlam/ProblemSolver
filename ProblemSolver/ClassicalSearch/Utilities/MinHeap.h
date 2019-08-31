#pragma once

#include <vector>
#include "SearchNode.h"

class MinHeap{
private :
	std::vector<SearchNode*> nodes;
	void swap(int i, int j);
	int parent(int index);
	int left(int index);
	int right(int index);

public :
	void heapify(int index);
	void push(SearchNode* node);
	SearchNode* pop();
	std::vector<SearchNode*>* getNodes();
	bool isEmpty();
};

