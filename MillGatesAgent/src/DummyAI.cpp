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
	ExpVector<Action> actions = state->getActions();
	return actions.get(rand() % actions.getLogicSize());
}

DummyAI::~DummyAI() {}

