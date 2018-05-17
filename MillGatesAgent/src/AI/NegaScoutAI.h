/*
 * NegaScoutAI.h
 *
 *  Created on: May 11, 2018
 *      Author: Luca
 */

#ifndef AI_NEGASCOUTAI_H_
#define AI_NEGASCOUTAI_H_

#include "../Utils/ExpVector.h"
#include "../Utils/HashSet.h"
#include "AI.h"
#include "Hash/ZobristHashing.h"
#include "Heuristic/HeuristicFunction.h"
#include "Heuristic/PawnCountHeuristic.h"
#include "Heuristic/RomanianHeuristic.h"

class NegaScoutAI: public AI {
private:

	HashSet<entry> * _table;
	ExpVector<hashcode> * _history;
	ZobristHashing * _hasher;
	HeuristicFunction * _heuristic;
	uint8 _depth;
	bool _stopFlag;

	eval_t negaScout(State * state, hashcode quickhash, uint8 depth, eval_t alpha, eval_t beta, sint8 color);
	void recurprint(State * state, int depth, int curdepth);

	uint8 partition(State * state, ExpVector<State*> * states, ExpVector<hashcode> * hashes, ExpVector<eval_t> * values, ExpVector<Action> * actions, eval_t p, eval_t q, sint8 color, hashcode quickhash);

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

	void quickSort(State * state, ExpVector<State*> * states, ExpVector<hashcode> * hashes, ExpVector<eval_t> * values, ExpVector<Action> * actions, eval_t p, eval_t q, sint8 color, hashcode quickhash);
	void setMaxFirst(State * state, ExpVector<State*> * states, ExpVector<hashcode> * hashes, ExpVector<eval_t> * values, ExpVector<Action> * actions, eval_t p, eval_t q, sint8 color, hashcode quickhash);

	virtual ~NegaScoutAI();
};

#endif /* AI_NEGASCOUTAI_H_ */
