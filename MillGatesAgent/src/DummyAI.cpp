/*
 * DummyAI.cpp
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#include "DummyAI.h"
#include "ExpVector.h"
#include <time.h>
#include <stdlib.h>

DummyAI::DummyAI() {}

Action DummyAI::choose(State * state) {
	ExpVector<Action> * actions = state->getActions();
	Action result = actions->get(rand() % actions->getLogicSize());
	delete actions;
	return result;
}

void DummyAI::setDepth(uint8 depth) {

}

void DummyAI::print(State * root, int depth) {}

void DummyAI::clear() {}

void DummyAI::stop() {}

void DummyAI::addHistory(State * state) {}

void DummyAI::clearHistory() {}

DummyAI::~DummyAI() {}

