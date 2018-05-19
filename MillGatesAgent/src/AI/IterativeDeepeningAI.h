/*
 * IterativeDeepeningAI.h
 *
 *  Created on: May 10, 2018
 *      Author: Luca
 */

#ifndef AI_ITERATIVEDEEPENINGAI_H_
#define AI_ITERATIVEDEEPENINGAI_H_

#include "ParallelNegaScoutAI.h"

void * timer(void * args);

class IterativeDeepeningAI : public AI{
private:
	AI * _ai;
	Action _tempAction;

public:
	IterativeDeepeningAI();

	virtual void setAI(AI * ai);
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void clear();
	virtual void stop();
	virtual void print(State * root, int depth);
	virtual void addHistory(State * state);
	virtual void clearHistory();
	virtual ~IterativeDeepeningAI();

	void * refreshResult(State * state);
	void * timer();
};

#endif /* AI_ITERATIVEDEEPENINGAI_H_ */
