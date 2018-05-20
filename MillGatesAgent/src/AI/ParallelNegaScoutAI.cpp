/*
 * NegaScoutAI.cpp
 *
 *  Created on: May 11, 2018
 *      Author: Luca
 */

#include "ParallelNegaScoutAI.h"

#if defined(WINDOWS)
#include "windows.h"
#endif

#if defined(LINUX)
#include "unistd.h"
#endif

ParallelNegaScoutAI::ParallelNegaScoutAI() {
	_tables = new ExpVector<HashSet<entry_p>*>(NUM_CORES);
	_histories = new ExpVector<HashSet<bool>*>(NUM_CORES);
	for (int i = 0; i < NUM_CORES; i++) {
		_tables->add(new HashSet<entry_p>());
		_histories->add(new HashSet<bool>());

		_results[i].terminal = false;
	}
	_hasher = ZobristHashing::getInstance();
	_depth = MIN_SEARCH_DEPTH;
	_stopFlag = false;
	_heuristic = new RomanianHeuristic();
	_actions = new ExpVector<Action>();
	_hash = 0;
	_color = 1;
	_state = NULL;
}

uint8 ParallelNegaScoutAI::getDepth() {
	return _depth;
}

void ParallelNegaScoutAI::setDepth(uint8 depth) {
	_depth = depth;
}

void ParallelNegaScoutAI::clear() {
	for (uint8 i = 0; i < NUM_CORES; i++)
		_tables->get(i)->clear();
}

void ParallelNegaScoutAI::stop() {
	_stopFlag = true;
}

void ParallelNegaScoutAI::addHistory(State * state) {
	for(int i = 0; i<NUM_CORES; i++) {
		addHistory(state, i);
	}
}

void ParallelNegaScoutAI::addHistory(State * state, int tid) {
	_histories->get(tid)->add(_hasher->hash(state), true);
}

void ParallelNegaScoutAI::clearHistory() {
	for (uint8 i = 0; i < NUM_CORES; i++) {
		_histories->get(i)->clear();
	}
}

void ParallelNegaScoutAI::setMaxFirst(ExpVector<State*> * states,
		ExpVector<hashcode> * hashes, ExpVector<eval_t> * values,
		ExpVector<Action> * actions) {
	// Find max
	eval_t max = values->get(0);
	eval_t indexMax = 0;
	for (eval_t i = 1; i < values->getLogicSize(); i++) {
		if (values->get(i) > max) {
			max = values->get(i);
			indexMax = i;
		}
	}
	if (indexMax != 0) {
		actions->swap(0, indexMax);
		states->swap(0, indexMax);
		hashes->swap(0, indexMax);
		values->swap(0, indexMax);
	}
}

eval_t ParallelNegaScoutAI::negaScout(State * state, hashcode quickhash,
	uint8 depth, eval_t alpha, eval_t beta, sint8 color, int tid) {

	entry_p * e;
	bool presentInTable = _tables->get(tid)->get(quickhash, &e);
	if (presentInTable && e->depth > depth) {
		if (e->entryFlag == EXACT_P)
			return color * e->eval;
		if (e->entryFlag == ALPHA_PRUNE_P && color * e->eval > alpha)
			alpha = e->eval * color;
		if (e->entryFlag == BETA_PRUNE_P && color * e->eval < beta)
			beta = e->eval * color;
		if (alpha >= beta)
			return alpha;
	}
	else { //Check in the tables of the other threads (READONLY)
		for(int i=0; i<NUM_CORES; i++) {
			if (i!=tid) {
				presentInTable = _tables->get(i)->get(quickhash, &e);
				if (presentInTable && e->depth > depth) {
//					std::cout << "[" << tid << "] Found a match in table " << i << "\n";
					//Update my table with the entry, so I advantage of the work of the others
					_tables->get(tid)->add(quickhash, *e);
					//Then proceeds as above
					if (e->entryFlag == EXACT_P)
						return color * e->eval;
					if (e->entryFlag == ALPHA_PRUNE_P && color * e->eval > alpha)
						alpha = e->eval * color;
					if (e->entryFlag == BETA_PRUNE_P && color * e->eval < beta)
						beta = e->eval * color;
					if (alpha >= beta)
						return alpha;
				}
			}
		}
	}

	eval_t score = 0;
	bool terminal = state->isTerminal();
	bool loop = _histories->get(tid)->contains(quickhash) && depth != _depth + 1;

	if (depth == 0 || _stopFlag || loop || terminal) {
		score = ParallelNegaScoutAI::_heuristic->evaluate(state, terminal,
				loop);
		if (!presentInTable)
			_tables->get(tid)->add(quickhash, entry_p { depth, EXACT_P, score });
		else
			*e = {depth, EXACT_P, score};
		return color * score;
	}

	ExpVector<Action> * actions = state->getActions();
	ExpVector<State*> * states = new ExpVector<State*>(actions->getLogicSize());
	ExpVector<hashcode> * hashes = new ExpVector<hashcode>(
			actions->getLogicSize());
	ExpVector<eval_t> * values = new ExpVector<eval_t>(actions->getLogicSize());

	entry_p * e_tmp;

	bool child_loop, child_present;

	for (int i = 0; i < actions->getLogicSize(); i++) {

		states->add(state->result(actions->get(i)));
		hashes->add(_hasher->quickHash(state, actions->get(i), quickhash));
		child_present = _tables->get(tid)->get(hashes->get(i), &e_tmp);

		if (child_present && e_tmp->depth > depth - 1)
			values->add(e_tmp->eval * -color);
		else { //Else I have to estimate the value using function
			for(int g=0; g<NUM_CORES; g++) {
				if (g!=tid) {
					child_present = _tables->get(g)->get(hashes->get(i), &e_tmp);
					if (child_present && e_tmp->depth > depth - 1) {
						values->add(e_tmp->eval * -color);
						break;
					}
				}
			}
			if(!child_present) {//Else I have to estimate the value using function
				child_loop = _histories->get(tid)->contains(hashes->get(i));
				//If not present inside my history, check the others
				if(!child_loop) { //Check the others
					for(int f=0; f<NUM_CORES && !child_loop; f++) {
						if (f!=tid) {
							child_loop = _histories->get(f)->contains(hashes->get(i));
							if(child_loop) //If found, update the history
								_histories->get(tid)->add(hashes->get(i), child_loop);
						}
					}
				}
				//Estimate the value
				values->add(_heuristic->evaluate(states->get(i),
								states->get(i)->isTerminal(), child_loop) * -color);
			}
		}
	}

	setMaxFirst(states, hashes, values, actions);

	State * child = NULL;
	hashcode child_hash = 0;
	entryFlagParallel_t flag = ALPHA_PRUNE_P;
	for (eval_t i = 0; i < actions->getLogicSize(); i++) {

		child = states->get(i);
		child_hash = hashes->get(i);
		if (i == 0)
			score = -negaScout(child, child_hash, depth - 1, -beta, -alpha,
					-color, tid);
		else {
			score = -negaScout(child, child_hash, depth - 1, -alpha - 1, -alpha,
					-color, tid);
			if (score > alpha && score < beta)
				score = -negaScout(child, child_hash, depth - 1, -beta, -score,
						-color, tid);
		}
		delete child;
		states->set(i, NULL);

		if (score > alpha) {
			alpha = score;
			flag = EXACT_P;
		}

		if (alpha >= beta) {
			flag = BETA_PRUNE_P;
			break;
		}
	}
	delete actions;
	delete hashes;
	for (uint8 i = 0; i < states->getLogicSize(); i++)
		if (states->get(i) != NULL)
			delete states->get(i);
	delete states;
	delete values;

	if (!presentInTable) {
		_tables->get(tid)->add(quickhash, entry_p { depth, flag, (eval_t) (alpha * color) });
//		std::cout << "[" << tid << "] Added: " << quickhash << "\n";
	}
	else {
		*e = {depth, flag, (eval_t)(alpha * color)};
//		std::cout << "[" << tid << "] Updated: " << quickhash << "\n";
	}

	return alpha;

}

void * ParallelNegaScoutAI::negaScoutThread_helper(void * param) {
	return (reinterpret_cast<ParallelNegaScoutAI*>(param))->negaScoutThread();
}

void * ParallelNegaScoutAI::negaScoutThread() {

	int tid = pthread_self()%NUM_CORES;
	// TODO: debug
	std::cout << "Ciaone, sono il pthread " << tid << "\n";
//	for(int i = 0; i < actions->getLogicSize(); i++) {
//		std::cout << actions->get(i) << "\n";
//	}
	//TODO: debug

	State * child;
	hashcode quickhash;
	eval_t tempscore;
	_results[tid].score = -MAX_EVAL_T;
	ExpVector<Action>* actions = _actions;
	int num_actions_per_thread = (actions->getLogicSize() / NUM_CORES);
	int rest_of_actions = (actions->getLogicSize() % NUM_CORES);

	for (int k = tid * num_actions_per_thread;
					k < ((tid * num_actions_per_thread) + num_actions_per_thread
									+ ((tid == NUM_CORES - 1) ? rest_of_actions : 0));
					k++) {
		child = _state->result(_actions->get(k));
		if (child->isTerminal()) {
			_results[tid].terminal = true;
			_results[tid].a = actions->get(k);
			delete child;
			break;
		}
		quickhash = _hasher->quickHash(_state, actions->get(k), _hash);
		tempscore = -negaScout(child, quickhash, _depth, -MAX_EVAL_T, - _results[tid].score, - _color, tid);
		if (tempscore > _results[tid].score) {
			_results[tid].score = tempscore;
			_results[tid].a = actions->get(k);
		}
		delete child;
	}
	pthread_exit(NULL);
	return NULL;
}

Action ParallelNegaScoutAI::choose(State * state) {

	_stopFlag = false;
	_actions = state->getActions();
	Action res;
	_color = (state->getPlayer() == PAWN_WHITE) ? 1 : -1;
	eval_t score = - MAX_EVAL_T * _color;
	_state = state;
	_hash = _hasher->hash(state);

	// Thread creation
	pthread_t thread[NUM_CORES];
	int rc;

	for (int i = 0; i < NUM_CORES; i++) {
		rc = pthread_create(&thread[i], NULL, negaScoutThread_helper, this);
		std::cout << "Avviato thread: " << thread[i] << "\n";
		if (rc) {
			std::cout << "ERROR: " << rc;
			exit(-1);
		}
	}

	for (int t = 0; t < NUM_CORES; t++) {
		rc = pthread_join(thread[t], NULL);
	}

	//Yield the results
	for (int t = 0; t < NUM_CORES; t++) {
		if(_results[t].terminal){
			res = _results[t].a;
			break;
		}
		if(_results[t].score > score) {
			score = _results[t].score;
			res = _results[t].a;
		}
	}
	return res;
}

void ParallelNegaScoutAI::recurprint(State * state, int depth, int curdepth) {
	entry_p * val = NULL;
	ExpVector<Action> * actions = state->getActions();
	State * child = NULL;
	for (int j = 0; j < NUM_CORES; j++) {
		std::cout << "TABLE OF THREAD " << j << "\n ==== \n";
		for (int i = 0; i < actions->getLogicSize(); i++) {
			child = state->result(actions->get(i));
			_tables->get(j)->get(_hasher->hash(child), &val);
			if (val == NULL) {
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << actions->get(i) << " -> CUT \n";
			} else if (depth == curdepth) {
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << actions->get(i) << " -> " << (int) val->eval
						<< ", " << (int) val->entryFlag << ", "
						<< (int) val->depth << "\n";
			} else {
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << actions->get(i) << " { \n";
				recurprint(child, depth, curdepth + 1);
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << "} -> " << (int) val->eval << ", "
						<< (int) val->entryFlag << ", " << (int) val->depth
						<< "\n";
			}
		}
		delete child;
	}
}

void ParallelNegaScoutAI::print(State * state, int depth) {
	recurprint(state, depth, 0);
}

ParallelNegaScoutAI::~ParallelNegaScoutAI() {
	for (int i = 0; i < NUM_CORES; i++) {
		delete _tables->get(i);
		delete _histories->get(i);
	}
	delete _tables;
	delete _histories;
	delete _heuristic;
	delete _actions;
}
