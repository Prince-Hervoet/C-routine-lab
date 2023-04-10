#include "lms_routine.h"

// 创建一个协程
LmsRoutine* getRoutine(unsigned int cap, taskFunc task) {
	if (cap == 0 || task == nullptr) {
		return nullptr;
	}
	LmsRoutine* lr = new LmsRoutine();
	lr->cap = cap;
	lr->status = READY_STATUS;
	lr->task = task;
	return lr;
}