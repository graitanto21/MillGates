/*
 * MinMaxAI.h
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#ifndef MINMAXAI_H_
#define MINMAXAI_H_

#include "AI.h"

class MinMaxAI: public AI {
public:
	MinMaxAI();
	virtual ~MinMaxAI();
	virtual Action choose(State * state, pawn player);
};

#endif /* MINMAXAI_H_ */
