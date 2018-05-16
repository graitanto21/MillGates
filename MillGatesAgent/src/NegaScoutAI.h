/*
 * NegaScoutAI.h
 *
 *  Created on: May 11, 2018
 *      Author: Luca
 */

#ifndef NEGASCOUTAI_H_
#define NEGASCOUTAI_H_

#include "AI.h"
#include "ZobristHashing.h"
#include "ExpVector.h"
#include "TranspositionTable.h"

class NegaScoutAI: public AI {
private:

	TranspositionTable * _table;
	ExpVector<hashcode> * _history;
	ZobristHashing * _hasher;
	uint8 _depth;
	bool _stopFlag;

	eval_t evaluate(State * state, bool terminal, bool loop);
	eval_t negaScout(State * state, hashcode quickhash, uint8 depth, eval_t alpha, eval_t beta, sint8 color);
	void recurprint(State * state, int depth, int curdepth);

public:
	NegaScoutAI();
	virtual uint8 getDepth();
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void clear();
	virtual void stop();
	virtual void print(State * root, int depth);
	virtual void addHistory(State * state);
	virtual void clearHistory();
	virtual ~NegaScoutAI();
};

#endif /* NEGASCOUTAI_H_ */
