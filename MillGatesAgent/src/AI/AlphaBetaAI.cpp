/*
 * AlphaBetaAI.cpp
 *
 *  Created on: May 19, 2018
 *      Author: Luca
 */

#include "AlphaBetaAI.h"

AlphaBetaAI::AlphaBetaAI() {
	_heuristic = new RomanianHeuristic();
	_hasher = ZobristHashing::getInstance();
	_depth = MIN_SEARCH_DEPTH;
	_history = new HashSet<bool>();
	_stopFlag = false;
}

eval_t AlphaBetaAI::min(State * state, hashcode hash, eval_t alpha, eval_t beta, uint8 depth) {

	bool terminal = state->isTerminal();
	bool loop = _history->contains(hash);

	if (depth == 0 || _stopFlag || terminal || loop)
		return _heuristic->evaluate(state, terminal, loop);

	ExpVector<Action> * actions = state->getActions();
	State * child;
	hashcode child_hash;
	eval_t score = MAX_EVAL_T;
	eval_t tempScore = score;

	for (short i = 0; i < actions->getLogicSize(); i++) {
		child = state->result(actions->get(i));
		child_hash = _hasher->quickHash(state, actions->get(i), hash);
		tempScore = max(child, child_hash, alpha, beta, depth - 1);
		score = (score < tempScore) ? score : tempScore;
		if (score <= alpha) {
			delete child;
			break;
		}
		beta = (beta < score) ? beta : score;
		delete child;
	}

	delete actions;
	return score;
}

eval_t AlphaBetaAI::max(State * state, hashcode hash, eval_t alpha, eval_t beta, uint8 depth) {

	bool terminal = state->isTerminal();
	bool loop = _history->contains(hash);

	if (depth == 0 || _stopFlag || terminal || loop)
		return _heuristic->evaluate(state, terminal, loop);

	ExpVector<Action> * actions = state->getActions();
	State * child;
	hashcode child_hash;
	eval_t score = -MAX_EVAL_T;
	eval_t tempScore = score;

	for (short i = 0; i < actions->getLogicSize(); i++) {
		child = state->result(actions->get(i));
		child_hash = _hasher->quickHash(state, actions->get(i), hash);
		tempScore = min(child, child_hash, alpha, beta, depth - 1);
		score = (score > tempScore) ? score : tempScore;
		if (score >= beta) {
			delete child;
			break;
		}
		alpha = (alpha > score) ? alpha : score;
		delete child;
	}

	delete actions;
	return score;
}

Action AlphaBetaAI::choose(State * state) {

	_stopFlag = false;

	ExpVector<Action> * actions = state->getActions();
	State * child;
	hashcode child_hash, father_hash = _hasher->hash(state);
	Action action;
	eval_t best, temp;

	if (state->getPlayer() == PAWN_WHITE) {
		best = -MAX_EVAL_T;
		for (short i = 0; i < actions->getLogicSize(); i++) {
			child = state->result(actions->get(i));
			child_hash = _hasher->quickHash(state, actions->get(i), father_hash);
			temp = min(child, child_hash, MAX_EVAL_T, best, _depth);
			if (temp > best) {
				best = temp;
				action = actions->get(i);
			}
			delete child;
		}
	}
	else {
		best = MAX_EVAL_T;
		for (short i = 0; i < actions->getLogicSize(); i++) {
			child = state->result(actions->get(i));
			child_hash = _hasher->quickHash(state, actions->get(i), father_hash);
			temp = max(child, child_hash, -MAX_EVAL_T, best, _depth);
			if (temp < best) {
				best = temp;
				action = actions->get(i);
			}
			delete child;
		}
	}

	delete actions;
	return action;

}

void AlphaBetaAI::setDepth(uint8 depth) {
	_depth = depth;
}

void AlphaBetaAI::clear() {}

void AlphaBetaAI::print(State * root, int depth) {}

void AlphaBetaAI::stop() {
	_stopFlag = true;
}

void AlphaBetaAI::addHistory(State * state) {
	_history->add(_hasher->hash(state), true);
}

void AlphaBetaAI::clearHistory() {
	_history->clear();
}

AlphaBetaAI::~AlphaBetaAI() {
	delete _history;
	delete _heuristic;
}

