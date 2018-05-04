/*
 * DummyAI.cpp
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#include "DummyAI.h"
#include "NodeExpander.h"
#include "ExpVector.h"
#include <time.h>
#include <stdlib.h>

DummyAI::DummyAI() {}

Action DummyAI::choose(Node node) {
	NodeExpander expander;
	ExpVector<Action> actions = expander.expand(node);
	return actions.get(rand() % actions.getLogicSize());
}

DummyAI::~DummyAI() {}

