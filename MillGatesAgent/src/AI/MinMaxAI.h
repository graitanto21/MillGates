/*
 * MinMaxAI.h
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#ifndef AI_MINMAXAI_H_
#define AI_MINMAXAI_H_

#include "../Utils/ExpVector.h"
#include "AI.h"
#include "Hash/ZobristHashing.h"

class MinMaxAI: public AI {
private:

	std::vector<ExpVector<hashcode>*> * _table;
	ZobristHashing * _hasher;
	int _count;
	uint8 _depth;

	int evaluate(State * state);
	int min(State * state, hashcode hashcode, int level);
	int max(State * state, hashcode hashcode, int level);
	bool visited(hashcode hashcode);
	void add(hashcode hashcode);
	virtual void stop();

public:
	MinMaxAI();
	virtual ~MinMaxAI();
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void print(State * root, int depth);
	virtual void clear();
	virtual void addHistory(State * state);
	virtual void clearHistory();
};

#endif /* AI_MINMAXAI_H_ */
