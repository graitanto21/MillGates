/*
 * DummyAI.h
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#ifndef AI_DUMMYAI_H_
#define AI_DUMMYAI_H_

#include "AI.h"

class DummyAI : public AI{
public:
	DummyAI();
	virtual ~DummyAI();

	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void clear();
	virtual void stop();
	virtual void print(State * root, int depth);
	virtual void addHistory(State * state);
	virtual void clearHistory();
};

#endif /* AI_DUMMYAI_H_ */
