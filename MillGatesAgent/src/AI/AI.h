/*
 * AI.h
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#ifndef AI_AI_H_
#define AI_AI_H_

#include "../Domain/Action.h"
#include "../Domain/State.h"

typedef struct {
	uint8 depth;
	eval_t eval;
} entry;

class AI {
public:

	virtual Action choose(State * state) = 0;
	virtual void setDepth(uint8 depth) = 0;
	virtual void clear() = 0;
	virtual void print(State * root, int depth) = 0;
	virtual void stop() = 0;
	virtual void addHistory(State * state) = 0;
	virtual void clearHistory() = 0;
	virtual ~AI();

};

#endif /* AI_AI_H_ */
