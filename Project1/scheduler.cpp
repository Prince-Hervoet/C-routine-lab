#include "scheduler.h"

void packingFunc(uint32_t low32One, uint32_t hi32One, uint32_t low32Two, uint32_t hi32Two) {
	uintptr_t ptr1 = (uintptr_t)low32One | ((uintptr_t)hi32One << 32);
	LmsRoutine* lr = (LmsRoutine*)ptr1;

	uintptr_t ptr2 = (uintptr_t)low32Two | ((uintptr_t)hi32Two << 32);
	Scheduler* s = (Scheduler*)ptr2;
	lr->task(s);
	if (s->delRoutine(lr)) {
		s->routineSize--;
		s->runningRid = -1;
	}
}

// 创建一个调度器
Scheduler* openScheduler(unsigned int cap) {
	Scheduler* s = new Scheduler();
	s->cap = cap;
	s->queue = new SimpleQueue();
	return s;
}

// 删除协程
bool Scheduler::delRoutine(LmsRoutine* lr) {
	if (lr == nullptr) {
		return false;
	}
	if (this->runningLr != lr) {
		return false;
	}
	if (lr->sp) {
		delete lr->sp;
	}
	delete lr;
	return true;
}

// 添加一个协程
bool Scheduler::addRoutine(LmsRoutine* lr) {
	if (routineSize == cap || !lr) {
		return false;
	}
	int rid = mod++;
	routineSize++;
	lr->rid = rid;
	queueAddNode(queue, lr);
	return true;
}

// 启动协程
void Scheduler::resumeRoutine() {
	if (this->routineSize == 0) {
		return;
	}
	SimpleQueueNode* sn = removeFirstNode(queue);
	LmsRoutine* lr = sn->cur;
	delete sn;
	int rid = lr->rid;

	// 设置该协程为当前协程
	this->runningRid = rid;
	this->runningLr = lr;

	if (lr->status == READY_STATUS) {
		// 第一次加入执行
		getcontext(&lr->ctx);
		lr->ctx.uc_stack.ss_sp = this->shareMemory;
		lr->ctx.uc_stack.ss_size = DEFAULT_SIZE;
		lr->ctx.uc_link = &this->threadContext;

		uintptr_t ptr1 = (uintptr_t)lr;
		uintptr_t ptr2 = (uintptr_t)this;
		makecontext(&lr->ctx, (void (*)())packingFunc, 4, (uint32_t)ptr1, (uint32_t)(ptr1 >> 32), (uint32_t)ptr2, (uint32_t)(ptr2 >> 32));
		swapcontext(&this->threadContext, &lr->ctx);
	}
	else if (lr->status == SUSPEND_STATUS) {
		memcpy(this->shareMemory + DEFAULT_SIZE - lr->size, lr->sp, lr->size);
		this->runningLr = lr;
		this->runningRid = lr->rid;
		swapcontext(&this->threadContext, &lr->ctx);
	}
}

void Scheduler::yieldRoutine() {
	char flag = 0;
	int cap = this->runningLr->cap;
	int temp = this->shareMemory + DEFAULT_SIZE - &flag;
	if (cap >= temp) {
		runningLr->size = temp;
		if (!runningLr->sp) {
			runningLr->sp = new char[temp];
		}
		memcpy(runningLr->sp, &flag, temp);
		runningLr->status = SUSPEND_STATUS;
		queueAddNode(this->queue, runningLr);
		LmsRoutine* tempLr = runningLr;
		this->runningLr = nullptr;
		this->runningRid = -1;
		swapcontext(&tempLr->ctx, &this->threadContext);
	}
}