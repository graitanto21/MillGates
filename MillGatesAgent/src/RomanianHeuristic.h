/*
 * RomanianHeuristic.h
 *
 *  Created on: May 16, 2018
 *      Author: Luca
 */

#ifndef ROMANIANHEURISTIC_H_
#define ROMANIANHEURISTIC_H_

#include "HeuristicFunction.h"

class RomanianHeuristic: public HeuristicFunction {
public:
	RomanianHeuristic();
	virtual eval_t evaluate(State * state, bool terminal, bool loop);
	virtual ~RomanianHeuristic();
};

#endif /* ROMANIANHEURISTIC_H_ */
