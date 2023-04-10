#pragma once
#include "lms_routine.h"
class LmsRoutine;
class SimpleQueue;
class SimpleQueueNode {
public:
	unsigned int rid;
	LmsRoutine* cur;
	SimpleQueueNode* next;
	SimpleQueueNode* front;
};

class SimpleQueue {
public:
	SimpleQueueNode* head;
	SimpleQueueNode* tail;
	SimpleQueue() {}
	~SimpleQueue() {}
};

SimpleQueueNode* getFirstNode(SimpleQueue* queue);
void queueAddNode(SimpleQueue* queue, LmsRoutine* lr);
SimpleQueueNode* removeFirstNode(SimpleQueue* queue);
