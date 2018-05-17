/*
 * HeuristicFunction.cpp
 *
 *  Created on: May 16, 2018
 *      Author: Luca
 */

#include "HeuristicFunction.h"

eval_t HeuristicFunction::evaluate(State * state) {
	return evaluate(state, state->isTerminal(), false);
}

HeuristicFunction::~HeuristicFunction() {}

