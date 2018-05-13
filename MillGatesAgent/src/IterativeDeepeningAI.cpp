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
	// TODO Auto-generated constructor stub
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

sem_t semaphore;

void * IterativeDeepeningAI::refreshResult(State * state) {

	for(int depth = MIN_SEARCH_DEPTH; depth <= MAX_SEARCH_DEPTH; depth++) {
		setDepth(depth);
		_tempAction = _ai->choose(state);
		clear();
		std::cout << "Chosen action: " << _tempAction << " with depth " << depth << "\n";
	}

	sem_post(&semaphore);
	return NULL;

}

void * timer(void * args) {

	std::cout << "Timer start\n";
#if defined(WINDOWS)
	Sleep(50000);
#endif
#if defined(LINUX)
	sleep(50);
#endif
	std::cout << "Timer end\n";
	sem_post(&semaphore);
	return NULL;

}

static void * refreshResult_helper(void * args) {
	return (reinterpret_cast<IterativeDeepeningAI*>(((void**)args)[0]))->refreshResult(reinterpret_cast<State*>(((void**)args)[1]));
}

Action IterativeDeepeningAI::choose(State * state) {

	pthread_t ai_thread;
	pthread_t timer_thread;

	sem_init(&semaphore, 0, 0);

	void ** param = (void**)malloc(sizeof(void*) * 2);
	param[0] = this;
	param[1] = state;

	pthread_create(&ai_thread, NULL, refreshResult_helper, param);
	pthread_create(&timer_thread, NULL, timer, NULL);
	sem_wait(&semaphore);
	pthread_cancel(ai_thread);
	pthread_cancel(timer_thread);
	print(state, 1);
	free(param);
	sem_destroy(&semaphore);
	clear();
	return _tempAction;
}

IterativeDeepeningAI::~IterativeDeepeningAI() {
	// TODO Auto-generated destructor stub
}

