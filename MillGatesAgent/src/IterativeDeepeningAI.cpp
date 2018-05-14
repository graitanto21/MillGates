/*
 * IterativeDeepeningAI.cpp
 *
 *  Created on: May 10, 2018
 *      Author: Luca
 */

#include "IterativeDeepeningAI.h"
#include <pthread.h>
#include <semaphore.h>
#include "os.h"
#if defined(WINDOWS)
#endif
#include "windows.h"
#if defined(LINUX)
#include "unistd.h"
#endif

IterativeDeepeningAI::IterativeDeepeningAI() {
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	_ai = NULL;
}

void IterativeDeepeningAI::setAI(AI * ai) {
	_ai = ai;
}

void IterativeDeepeningAI::setDepth(uint8 depth) {
	_ai->setDepth(depth);
}

void IterativeDeepeningAI::print(State * root, int depth) {
	_ai->print(root, depth);
}

void IterativeDeepeningAI::clear() {
	_ai->clear();
}

bool timeUp = false;
bool computationFinished = false;

void * IterativeDeepeningAI::refreshResult(State * state) {

	computationFinished = false;
	std::cout << "Computation start\n";

//	for(int depth = MIN_SEARCH_DEPTH; depth <= MAX_SEARCH_DEPTH; depth++) {
//		setDepth(depth);
//		_tempAction = _ai->choose(state);
//		clear();
//		if (timeUp) {
//			std::cout << "Chosen action: " << _tempAction << " with depth " << depth << "\n";
//			break;
//		}
//	}

	Sleep(60000);

	computationFinished = true;
	std::cout << "Computation end\n";
	pthread_exit(NULL);
	return NULL;
}

void * timer(void * args) {

	std::cout << "Timer start\n";
	timeUp = false;
	for (int i = 0; i < COMPUTATION_TIME; i++) {
#if defined(WINDOWS)
		Sleep(1000);
#endif
#if defined(LINUX)
		sleep(1);
#endif
		if (computationFinished)
			break;
	}
	std::cout << "Timer end\n";
	timeUp = true;
	pthread_exit(NULL);
	return NULL;

}

static void * refreshResult_helper(void * args) {
	return (reinterpret_cast<IterativeDeepeningAI*>(((void**)args)[0]))->refreshResult(reinterpret_cast<State*>(((void**)args)[1]));
}

Action IterativeDeepeningAI::choose(State * state) {

	pthread_t ai_thread;
	pthread_t timer_thread;

	void ** param = (void**)malloc(sizeof(void*) * 2);
	param[0] = this;
	param[1] = state;

	pthread_create(&ai_thread, NULL, refreshResult_helper, param);
	pthread_create(&timer_thread, NULL, timer, NULL);
	pthread_join(timer_thread, NULL);
	if (!computationFinished)
		pthread_cancel(ai_thread);
	print(state, 0);
	free(param);
	clear();
	return _tempAction;
}

IterativeDeepeningAI::~IterativeDeepeningAI() {
	// TODO Auto-generated destructor stub
}

