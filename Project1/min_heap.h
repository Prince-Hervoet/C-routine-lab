#pragma once
#include <vector>
#include "scheduler.h"

class MinHeap {
private:
	int cap;
	std::vector<Scheduler*>* arr;
	void heapify(int index);
	void heapUp(int index);
public:
	int getSize();
	void addNode();
	Scheduler* getFirstNode();
	MinHeap(int cap) {
		this->cap = cap;
	};
};
