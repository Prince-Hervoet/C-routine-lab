#pragma once
#include <ucontext.h>
// 就绪
#define READY_STATUS 1
// 正在运行
#define RUNNING_STATUS 2
// 暂停
#define SUSPEND_STATUS 4
// 已经死亡
#define DEAD_STATUS 8
// 协程结构

class Scheduler;
typedef void(*taskFunc)(Scheduler*);
class LmsRoutine {
public:
	LmsRoutine() {}
	LmsRoutine(int status, unsigned int size, taskFunc task)
		:status(status), task(task)
	{
	}
	// 协程当前状态
	int status;
	// 上下文
	ucontext_t ctx;
	// 执行任务
	taskFunc task;
	// 栈顶指针
	char* sp = nullptr;
	// 当前协程大小
	unsigned int size;
	// 分配的大小
	unsigned int cap;
	// rid
	unsigned int rid;
};
// 创建一个协程
LmsRoutine* getRoutine(unsigned int size, taskFunc task);