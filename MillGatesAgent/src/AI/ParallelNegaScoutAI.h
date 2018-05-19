/*
 * NegaScoutAI.h
 *
 *  Created on: May 19, 2018
 *      Author: Lorenzo Rosa
 */

#ifndef AI_PARALLELNEGASCOUTAI_H_
#define AI_PARALLELNEGASCOUTAI_H_

#include "../Utils/ExpVector.h"
#include "../Utils/HashSet.h"
#include "AI.h"
#include "Hash/ZobristHashing.h"
#include "Heuristic/HeuristicFunction.h"
#include "Heuristic/PawnCountHeuristic.h"
#include "Heuristic/RomanianHeuristic.h"

#include <pthread.h>
#include <semaphore.h>
#include "../os.h"
#if defined(WINDOWS)
#endif
#include "windows.h"
#if defined(LINUX)
#include "unistd.h"
#endif

typedef enum entryFlag_t {EXACT, ALPHA_PRUNE, BETA_PRUNE} entryFlag_t;

typedef struct {
	uint8 depth;
	entryFlag_t entryFlag;
	eval_t eval;
} entry;

typedef struct {
	pthread_t tid;
	State * state;
	ExpVector<Action> * actions;
	hashcode hash;
	sint8 color;
	uint8 depth;
} args;

class ParallelNegaScoutAI: public AI {
private:
	ExpVector<HashSet<entry>*> * _tables;
	ExpVector<HashSet<bool>*> * _histories;
	ZobristHashing * _hasher;
	HeuristicFunction * _heuristic;
	uint8 _depth;
	bool _stopFlag;

	void recurprint(State * state, int depth, int curdepth);

	uint8 partition(State * state, ExpVector<State*> * states, ExpVector<hashcode> * hashes, ExpVector<eval_t> * values, ExpVector<Action> * actions, eval_t p, eval_t q, sint8 color, hashcode quickhash);

public:
	ParallelNegaScoutAI();
	virtual uint8 getDepth();
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
	virtual void clear();
	virtual void stop();
	virtual void print(State * root, int depth);
	virtual void addHistory(State * state);
	virtual void addHistory(State * state,  int tid);
	virtual void clearHistory();

	static void * negaScoutThread_helper(void * arg);
	void * negaScoutThread(args * arg);
	eval_t negaScout(State * state, hashcode quickhash, uint8 depth, eval_t alpha, eval_t beta, sint8 color, int tid);

	void setMaxFirst(ExpVector<State*> * states, ExpVector<hashcode> * hashes, ExpVector<eval_t> * values, ExpVector<Action> * actions);

	virtual ~ParallelNegaScoutAI();
};

#endif /* AI_PARALLELNEGASCOUTAI_H_ */
