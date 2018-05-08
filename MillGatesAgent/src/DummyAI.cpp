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

Action DummyAI::choose(State * state, pawn player) {
	ExpVector<Action> actions = state->getActions(player);
	return actions.get(rand() % actions.getLogicSize());
}

DummyAI::~DummyAI() {}

