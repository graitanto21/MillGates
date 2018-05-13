/*
 * IterativeDeepeningAI.cpp
 *
 *  Created on: May 10, 2018
 *      Author: Luca
 */

#include "IterativeDeepeningAI.h"

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

Action IterativeDeepeningAI::choose(State * state) {
	Action result;

	for(int i = MAX_SEARCH_DEPTH; i <= MAX_SEARCH_DEPTH; i++) {
		setDepth(i);
		result = _ai->choose(state);
		std::cout << "Chosen action: " <<result << "\n";
		// if time_out() break;
	}

	print(state, 1);

	clear();

	return result;
}

IterativeDeepeningAI::~IterativeDeepeningAI() {
	// TODO Auto-generated destructor stub
}

