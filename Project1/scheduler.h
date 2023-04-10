#pragma once
#include <ucontext.h>
#include <cstdint>
#include "lms_routine.h"
#include "simple_queue.h"
#include <string.h>
#include <assert.h>

// Ĭ�Ϲ�����С
#define DEFAULT_SIZE 262144
class LmsRoutine;
class SimpleQueue;
// Э�̵�����
class Scheduler {
	friend void packingFunc(uint32_t low32One, uint32_t hi32One, uint32_t low32Two, uint32_t hi32Two);
	friend Scheduler* openScheduler(unsigned int cap);
private:
	// ��ǰӵ�е�Э������
	int routineSize;
	// ��ǰ�������е�Э��id
	unsigned int runningRid = -1;
	// ��ǰ�������е�Э��
	LmsRoutine* runningLr = nullptr;
	// ����
	unsigned int mod;
	// �˹����������ɵ����Э����
	unsigned int cap;
	// �������Э��
	SimpleQueue* queue;
	// ���̵߳�������
	ucontext_t threadContext;
	// ����ջ��С
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
