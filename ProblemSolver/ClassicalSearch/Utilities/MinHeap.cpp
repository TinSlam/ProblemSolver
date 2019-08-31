#include "MinHeap.h"

void MinHeap::push(SearchNode* node){
	nodes.push_back(node);
 
	int i = (int) nodes.size() - 1;
	while(i != 0 && nodes[parent(i)]->getFValue() > nodes[i]->getFValue()){
		swap(i, parent(i));
		i = parent(i);
	}
}

SearchNode * MinHeap::pop(){
	if(nodes.empty())
		return nullptr;

	SearchNode* node = nodes.front();
	if(nodes.size() == 1){
		nodes.pop_back();
		return node;
	}

	// Store the minimum value, and remove it from heap
	nodes[0] = nodes.back();
	nodes.pop_back();
	heapify(0);

	return node;
}

std::vector<SearchNode*>* MinHeap::getNodes(){
	return &nodes;
}

void MinHeap::heapify(int index){
	unsigned int l = left(index);
	unsigned int r = right(index);
	unsigned int smallest = index;
	if(l < nodes.size() && nodes[l]->getFValue() < nodes[index]->getFValue())
		smallest = l;
	if(r < nodes.size() && nodes[r]->getFValue() < nodes[smallest]->getFValue())
		smallest = r;
	if(smallest != index){
		swap(index, smallest);
		heapify(smallest);
	}
}

void MinHeap::swap(int i, int j){
	SearchNode* node = nodes[i];
	nodes[i] = nodes[j];
	nodes[j] = node;
}

int MinHeap::parent(int index){
	return (index - 1) / 2;
}

int MinHeap::left(int index){
	return (2 * index + 1);
}

int MinHeap::right(int index){
	return (2 * index + 2);
}

bool MinHeap::isEmpty(){
	return nodes.empty();
}