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
	//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
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

void IterativeDeepeningAI::stop() {
	_ai->stop();
}

bool timeUp = false;
bool aiComputing = false;

void * IterativeDeepeningAI::refreshResult(State * state) {

	aiComputing = true;
	std::cout << "Computation start\n";
	Action lastChosen;

	for(int depth = MIN_SEARCH_DEPTH; depth <= MAX_SEARCH_DEPTH; depth++) {
		std::cout << "Choosing an action with depth " << depth << "\n";
		setDepth(depth);
		lastChosen = _ai->choose(state);
		clear();
		if (timeUp) {
			std::cout << "Chosen action: " << _tempAction << " with depth " << depth << "\n";
			break;
		}
		else
			_tempAction = lastChosen;
	}

	aiComputing = false;
	std::cout << "Computation end\n";
	pthread_exit(NULL);
	return NULL;
}

void * IterativeDeepeningAI::timer() {

	std::cout << "Timer start\n";
	timeUp = false;
	for (int i = 0; i < COMPUTATION_TIME; i++) {
#if defined(WINDOWS)
		Sleep(1000);
#endif
#if defined(LINUX)
		sleep(1);
#endif
		if (!aiComputing)
			break;
	}
	std::cout << "Timer end\n";
	timeUp = true;
	this->stop();
	pthread_exit(NULL);
	return NULL;

}

static void * refreshResult_helper(void * args) {
	return (reinterpret_cast<IterativeDeepeningAI*>(((void**)args)[0]))->refreshResult(reinterpret_cast<State*>(((void**)args)[1]));
}

static void * timer_helper(void * context) {
	return (reinterpret_cast<IterativeDeepeningAI*>(context))->timer();
}

Action IterativeDeepeningAI::choose(State * state) {

	pthread_t ai_thread;
	pthread_t timer_thread;

	void ** param = (void**)malloc(sizeof(void*) * 2);
	param[0] = this;
	param[1] = state;

	pthread_create(&ai_thread, NULL, refreshResult_helper, param);
	pthread_create(&timer_thread, NULL, timer_helper, this);
	//pthread_join(timer_thread, NULL);
	pthread_join(ai_thread, NULL);
	print(state, 0);
	free(param);
	clear();
	return _tempAction;
}

IterativeDeepeningAI::~IterativeDeepeningAI() {
	// TODO Auto-generated destructor stub
}

