#include "min_heap.h"

void MinHeap::heapUp(int index) {
	if (index < 0 || index >= this->arr->size()) {
		return;
	}
	int parentIndex = (index - 1) >> 1;
	if (parentIndex == index) {
		return;
	}
	while (arr->at(parentIndex)->getRoutineSize() > arr->at(index)->getRoutineSize()) {
		Scheduler* temp = (*arr)[parentIndex];
		(*arr)[parentIndex] = (*arr)[index];
		(*arr)[index] = temp;
		index = parentIndex;
		parentIndex = (index - 1) >> 1;
	}
}

void MinHeap::heapify(int index) {
	if (index < 0 || index >= this->arr->size()) {
		return;
	}
	int minIndex = 0;
	do {
		int leftIndex = index * 2 + 1;
		int rightIndex = leftIndex + 1;
		if (leftIndex >= this->arr->size()) {
			return;
		}
		minIndex = leftIndex;
		if (rightIndex < this->arr->size()) {
			if (arr->at(rightIndex)->getRoutineSize() < arr->at(leftIndex)->getRoutineSize()) {
				minIndex = rightIndex;
			}
		}
	} while (arr->at(index)->getRoutineSize() > arr->at(minIndex)->getRoutineSize());
}