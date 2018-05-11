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

typedef struct {
	sint8 depth;
	sint8 eval;
	hashcode hash;
} entry;

class NegaScoutAI: public AI {
private:

	std::vector<ExpVector<entry*>*> * _hashes;
	ZobristHashing * _hasher;
	int _count;
	uint8 _depth;

	sint8 evaluate(State * state);
	entry * get(hashcode hashcode);
	void add(entry * entry);

	sint8 negaScout(State * state, hashcode quickhash, uint8 depth, sint8 alpha, sint8 beta, sint8 color);

public:
	NegaScoutAI();
	Action choose(State * state);
	virtual ~NegaScoutAI();
};

#endif /* NEGASCOUTAI_H_ */
