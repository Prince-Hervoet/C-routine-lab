#include "simple_queue.h"
void queueAddNode(SimpleQueue* queue, LmsRoutine* lr) {
	if (!lr) {
		return;
	}
	SimpleQueueNode* node = new SimpleQueueNode();
	node->cur = lr;
	node->next = nullptr;
	node->front = nullptr;

	if (queue->head == nullptr) {
		queue->head = node;
		queue->tail = node;
	}
	else {
		queue->tail->next = node;
		node->front = queue->tail;
		queue->tail = node;
	}
}

SimpleQueueNode* getFirstNode(SimpleQueue* queue) {
	if (!queue || !queue->head) {
		return nullptr;
	}
	return queue->head;
}

SimpleQueueNode* removeFirstNode(SimpleQueue* queue) {
	if (!queue || !queue->head) {
		return nullptr;
	}
	SimpleQueueNode* ans = queue->head;
	SimpleQueueNode* temp = ans->next;
	ans->next = nullptr;
	if (temp) {
		temp->front = nullptr;
	}
	queue->head = temp;
	if (!queue->head) {
		queue->tail = nullptr;
	}
	return ans;
}