/*
 * NegaScoutAI.cpp
 *
 *  Created on: May 11, 2018
 *      Author: Luca
 */

#include "NegaScoutAI.h"

NegaScoutAI::NegaScoutAI() {
	_table = new TranspositionTable();
	_hasher = ZobristHashing::getInstance();
	_depth = MIN_SEARCH_DEPTH;
	_stopFlag = false;
	_history = new ExpVector<hashcode>();
	_heuristic = new RomanianHeuristic();
}

eval_t NegaScoutAI::negaScout(State * state, hashcode quickhash, uint8 depth, eval_t alpha, eval_t beta, sint8 color) {

	entry * e = _table->get(quickhash);
	if (e != NULL && e->depth > depth)
		//if (e != NULL)
		return color * e->eval;

	eval_t score = 0;
	bool terminal = false;
	bool loop = false;

	for (short i = _history->getLogicSize() - 1; i >= 0; i--)
		if (_history->get(i) == quickhash && _depth + 1 != depth) {
			loop = true;
			break;
		}

	if (depth == 0 || _stopFlag || loop || (terminal = state->isTerminal())) {
		score = _heuristic->evaluate(state, terminal, loop);
		if (e == NULL) {
			e = new entry();
			e->depth = depth;
			e->eval = score;
			e->hash = quickhash;
			_table->add(e);
		}
		else {
			e->eval = score;
			e->depth = depth;
		}
		return color * score;
	}

	hashcode child_hash = 0;
	ExpVector<Action> * actions = state->getActions();
	ExpVector<State*> * states = sortActionsByValue(state, actions, color, quickhash, terminal, loop);
	State * child = NULL;
	for (uint8 i = 0; i < actions->getLogicSize(); i++) {
		//child = state->result(actions->get(i));
		child = states->get(i);
		child_hash = _hasher->quickHash(state, actions->get(i), quickhash);
		if(i != 0) {
			score = -negaScout(child, child_hash, depth - 1, -alpha - 1, -alpha, -color);
			if (score > alpha && score < beta)
				score = -negaScout(child, child_hash, depth - 1, -beta, -score, -color);
		}
		else
			score = -negaScout(child, child_hash, depth - 1, -beta, -alpha, -color);

		delete child;

		alpha = (alpha > score) ? alpha : score;
		if (alpha >= beta || _stopFlag)
			break;
	}
	delete actions;
	delete states;

	if (e == NULL) {
		e = new entry();
		e->depth = depth;
		e->eval = color * alpha;
		e->hash = quickhash;
		_table->add(e);
	}
	else {
		e->eval = color * alpha;
		e->depth = depth;
	}

	return alpha;

}

uint8 NegaScoutAI::getDepth() {
	return _depth;
}

void NegaScoutAI::setDepth(uint8 depth) {
	_depth = depth;
}

void NegaScoutAI::clear() {
	_table->clear();
}

void NegaScoutAI::stop() {
	_stopFlag = true;
}

void NegaScoutAI::addHistory(State * state) {
	_history->add(_hasher->hash(state));
}

void NegaScoutAI::clearHistory() {
	delete _history;
	_history = new ExpVector<hashcode>();
}

Action NegaScoutAI::choose(State * state) {

	_stopFlag = false;
	//	if (state->getPawnsToPlay(state->getPlayer()) == 9)
	//		return Action(POS_NULL, NEW_POS(2,2,1), POS_NULL);

	ExpVector<Action> * actions = state->getActions();

	Action res;
	eval_t score;
	entry * tempscore;
	hashcode quickhash, hash;

	hash = _hasher->hash(state);

	if (state->getPlayer() == PAWN_WHITE) {
		negaScout(state, hash, _depth + 1, -MAX_EVAL_T, MAX_EVAL_T, 1);
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			quickhash = _hasher->quickHash(state, actions->get(i), hash);
			tempscore = _table->get(quickhash);
			if (tempscore != NULL) {
				if (i == 0 || tempscore->eval > score) {
					score = tempscore->eval;
					res = actions->get(i);
				}
			}
			else {
				std::cout << "NOT FOUND " << quickhash << " -> " << actions->get(i) << "\n";
				res = actions->get(0);
			}
		}
	}
	else {
		negaScout(state, hash, _depth + 1, -MAX_EVAL_T, MAX_EVAL_T, -1);
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			quickhash = _hasher->quickHash(state, actions->get(i), hash);
			tempscore = _table->get(quickhash);
			if (tempscore != NULL) {
				if (i == 0 || tempscore->eval < score) {
					score = tempscore->eval;
					res = actions->get(i);
				}
			}
			else {
				std::cout << "NOT FOUND " << quickhash << " -> " << actions->get(i) << "\n";
				res = actions->get(0);
			}
		}
	}

	delete actions;

	return res;
}

void NegaScoutAI::recurprint(State * state, int depth, int curdepth) {
	entry * val = NULL;
	ExpVector<Action> * actions = state->getActions();
	State * child = NULL;
	for (int i = 0; i < actions->getLogicSize(); i++) {
		child = state->result(actions->get(i));
		val = _table->get(_hasher->hash(child));
		if (val == NULL) {
			for (int j = 0; j < curdepth; j++)
				std::cout << " | ";
			std::cout << actions->get(i) << " -> CUT \n";
		}
		else if (depth == curdepth) {
			for (int j = 0; j < curdepth; j++)
				std::cout << " | ";
			std::cout << actions->get(i) << " -> " << (int)val->eval << "\n";
		}
		else {
			for (int j = 0; j < curdepth; j++)
				std::cout << " | ";
			std::cout << actions->get(i) << " { \n";
			recurprint(child, depth, curdepth + 1);
			for (int j = 0; j < curdepth; j++)
				std::cout << " | ";
			std::cout << "} -> " << (int)val->eval << "\n";
		}
		delete child;
	}
}

void NegaScoutAI::print(State * state, int depth) {

	recurprint(state, depth, 0);

}

ExpVector<State*> * NegaScoutAI::sortActionsByValue(State * state, ExpVector<Action>* actions, sint8 color, hashcode quickhash, bool terminal, bool loop) {
	ExpVector<State*> * res = new ExpVector<State*>(actions->getLogicSize());
	quickSort(state, res, actions, 0, actions->getLogicSize()-1, color, quickhash, terminal, loop);
	return res;
}

void NegaScoutAI::quickSort(State*state, ExpVector<State*> * states, ExpVector<Action> * actions, uint8 p, uint8 q, sint8 color, hashcode quickhash, bool terminal, bool loop) {
	uint8 r;
	if(p<q) {
		r = partition(state, states, actions, p, q, color, quickhash, terminal, loop);
		quickSort(state, states, actions, p, r, color, quickhash, terminal, loop);
		quickSort(state, states, actions, r+1, q, color, quickhash, terminal, loop);
	}
}

uint8 NegaScoutAI::partition(State*state, ExpVector<State*> * states, ExpVector<Action> * actions, uint8 p, uint8 q, sint8 color, hashcode quickhash, bool terminal, bool loop){
	sint8 x = (state->result(actions->get(p)))->utility();
	uint8 i = p;
	uint8 j;

	hashcode child_hash;
	sint8 value;
	entry * e;

	for(j=p+1; j<q; j++)   {
		//Determine the value

		states->set(j, state->result(actions->get(j)));

		child_hash = _hasher->quickHash(state, actions->get(i), quickhash);

		//If I have the value of the state resulting from the Action, I use it
		e = _table->get(child_hash);
		if (e != NULL)
			value = e->eval * color;
		else //Else I have to estimate the value using function
			value = _heuristic->evaluate(states->get(j), terminal, loop) * color;
		std::cout << "VALUE: " << (int)value << "\n";

		if (value >= x){
			i=i+1;
			actions->swap(actions->get(i), actions->get(j));
			std::cout << "SWAP : " << actions->get(i) << actions->get(j) << "\n";
			states->swap(states->get(i), states->get(j));
		}
	}
	actions->swap(actions->get(i), actions->get(p));
	states->swap(states->get(i), states->get(p));
	return i;
}

NegaScoutAI::~NegaScoutAI() {
	delete _table;
	delete _history;
	delete _heuristic;
}

