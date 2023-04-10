#pragma once
#include <ucontext.h>
// ����
#define READY_STATUS 1
// ��������
#define RUNNING_STATUS 2
// ��ͣ
#define SUSPEND_STATUS 4
// �Ѿ�����
#define DEAD_STATUS 8
// Э�̽ṹ

class Scheduler;
typedef void(*taskFunc)(Scheduler*);
class LmsRoutine {
public:
	LmsRoutine() {}
	LmsRoutine(int status, unsigned int size, taskFunc task)
		:status(status), task(task)
	{
	}
	// Э�̵�ǰ״̬
	int status;
	// ������
	ucontext_t ctx;
	// ִ������
	taskFunc task;
	// ջ��ָ��
	char* sp = nullptr;
	// ��ǰЭ�̴�С
	unsigned int size;
	// ����Ĵ�С
	unsigned int cap;
	// rid
	unsigned int rid;
};
// ����һ��Э��
LmsRoutine* getRoutine(unsigned int size, taskFunc task);