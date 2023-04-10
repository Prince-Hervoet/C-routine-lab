#include "scheduler.h"
#include <iostream>

Scheduler* openScheduler(unsigned int cap);

void foo1(Scheduler* s) {
	for (int i = 0; i < 5; i++) {
		std::cout << "i am 1" << std::endl;
		s->yieldRoutine();
	}
}

void foo2(Scheduler* s) {
	for (int i = 0; i < 5; i++) {
		std::cout << "i am 2" << std::endl;
		s->yieldRoutine();
	}
}

int main() {
	Scheduler* s = openScheduler(10);
	LmsRoutine* lr1 = getRoutine(200, foo1);
	LmsRoutine* lr2 = getRoutine(200, foo2);
	s->addRoutine(lr2);
	s->addRoutine(lr1);
	while (s->getRoutineSize()) {
		s->resumeRoutine();
	}
	while (1) {
	}
}