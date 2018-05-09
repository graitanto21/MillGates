/*
 * MinMaxAI.h
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#ifndef MINMAXAI_H_
#define MINMAXAI_H_

#include "AI.h"
#include "ExpVector.h"
#include "ZobristHashing.h"

class MinMaxAI: public AI {
private:

	ExpVector<int> * _hashes;
	ZobristHashing * _hasher;

	int min(State * state);
	int max(State * state);

public:
	MinMaxAI();
	virtual ~MinMaxAI();
	virtual Action choose(State * state);
};

#endif /* MINMAXAI_H_ */
