#pragma once
#include <ucontext.h>
#include <cstdint>
#include "lms_routine.h"
#include "simple_queue.h"
#include <string.h>
#include <assert.h>

// 默认共享库大小
#define DEFAULT_SIZE 262144
class LmsRoutine;
class SimpleQueue;
// 协程调度器
class Scheduler {
	friend void packingFunc(uint32_t low32One, uint32_t hi32One, uint32_t low32Two, uint32_t hi32Two);
	friend Scheduler* openScheduler(unsigned int cap);
private:
	// 当前拥有的协程数量
	int routineSize;
	// 当前正在运行的协程id
	unsigned int runningRid = -1;
	// 当前正在运行的协程
	LmsRoutine* runningLr = nullptr;
	// 递增
	unsigned int mod;
	// 此管理器能容纳的最大协程数
	unsigned int cap;
	// 存放所有协程
	SimpleQueue* queue;
	// 主线程的上下文
	ucontext_t threadContext;
	// 共享栈大小
	char shareMemory[DEFAULT_SIZE];

	Scheduler() {
	}
public:
	bool addRoutine(LmsRoutine* lr);
	void resumeRoutine();
	void yieldRoutine();
	bool delRoutine(LmsRoutine* lr);
	int getRoutineSize() {
		return this->routineSize;
	}

	~Scheduler() {
		delete this->queue;
	}
};
