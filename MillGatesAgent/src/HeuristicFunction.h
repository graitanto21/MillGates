/*
 * HeuristicFunction.h
 *
 *  Created on: May 16, 2018
 *      Author: Luca
 */

#ifndef HEURISTICFUNCTION_H_
#define HEURISTICFUNCTION_H_

#include "Commons.h"
#include "State.h"

class HeuristicFunction {
public:
	virtual eval_t evaluate(State * state, bool terminal, bool loop) = 0;
	virtual eval_t evaluate(State * state);
	virtual ~HeuristicFunction();
};

#endif /* HEURISTICFUNCTION_H_ */
