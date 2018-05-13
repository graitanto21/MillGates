/*
 * IterativeDeepeningAI.h
 *
 *  Created on: May 10, 2018
 *      Author: Luca
 */

#ifndef ITERATIVEDEEPENINGAI_H_
#define ITERATIVEDEEPENINGAI_H_

#include "NegaScoutAI.h"

class IterativeDeepeningAI {
private:
	AI * _ai;
public:
	IterativeDeepeningAI();

	virtual void setAI(AI * ai);
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void clear();
	virtual void print(State * root, int depth);
	virtual ~IterativeDeepeningAI();
};

#endif /* ITERATIVEDEEPENINGAI_H_ */
