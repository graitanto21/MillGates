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
	ZobristHashing * _hasher;
	uint8 _depth;
	bool _stopFlag;

	sint8 evaluate(State * state);
	sint8 negaScout(State * state, hashcode quickhash, uint8 depth, sint8 alpha, sint8 beta, sint8 color);
	void recurprint(State * state, int depth, int curdepth);

public:
	NegaScoutAI();
	virtual uint8 getDepth();
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void clear();
	virtual void stop();
	virtual void print(State * root, int depth);
	virtual ~NegaScoutAI();
};

#endif /* NEGASCOUTAI_H_ */
