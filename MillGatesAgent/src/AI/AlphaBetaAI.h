/*
 * AlphaBetaAI.h
 *
 *  Created on: May 19, 2018
 *      Author: Luca
 */

#ifndef AI_ALPHABETAAI_H_
#define AI_ALPHABETAAI_H_

#include "AI.h"
#include "Hash/ZobristHashing.h"
#include "../Utils/HashSet.h"
#include "Heuristic/RomanianHeuristic.h"
#include "Heuristic/PawnCountHeuristic.h"

class AlphaBetaAI : public AI{
private :

	HashSet<bool> * _history;
	ZobristHashing * _hasher;
	HeuristicFunction * _heuristic;
	uint8 _depth;
	bool _stopFlag;

	eval_t min(State * state, hashcode hash, eval_t alpha, eval_t beta, uint8 depth);
	eval_t max(State * state, hashcode hash, eval_t alpha, eval_t beta, uint8 depth);

public:
	AlphaBetaAI();

	virtual Action choose(State * state);
	virtual void setDepth(uint8 depth);
	virtual void clear();
	virtual void print(State * root, int depth);
	virtual void stop();
	virtual void addHistory(State * state);
	virtual void clearHistory();

	virtual ~AlphaBetaAI();
};

#endif /* AI_ALPHABETAAI_H_ */
