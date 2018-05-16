/*
 * PawnCountHeuristic.h
 *
 *  Created on: May 16, 2018
 *      Author: Luca
 */

#ifndef PAWNCOUNTHEURISTIC_H_
#define PAWNCOUNTHEURISTIC_H_

#include "HeuristicFunction.h"

class PawnCountHeuristic: public HeuristicFunction {
public:
	PawnCountHeuristic();
	virtual eval_t evaluate(State * state, bool terminal, bool loop);
	virtual ~PawnCountHeuristic();
};

#endif /* PAWNCOUNTHEURISTIC_H_ */
