/*
 * NegaScoutAI.cpp
 *
 *  Created on: May 11, 2018
 *      Author: Luca
 */

#include "NegaScoutAI.h"

#define DEPTH 7
//#define PRINT_COUNT
//#define PRINT_ADDED_HASHES
#define PRINT_GRANULARITY 10000

sint8 NegaScoutAI::evaluate(State * state) {
	sint8 white = state->getPawnsOnBoard(PAWN_WHITE) + state->getPawnsToPlay(PAWN_WHITE);
	sint8 black = state->getPawnsOnBoard(PAWN_BLACK) + state->getPawnsToPlay(PAWN_BLACK);

	return white - black;
}

entry * NegaScoutAI::get(hashcode hashcode) {
	ExpVector<entry*> * vec = (*_hashes)[hashcode & HASH_MASK];
	for (int i = 0; i < vec->getLogicSize(); i++)
		if (vec->get(i)->hash == hashcode)
			return vec->get(i);
	return NULL;
}

void NegaScoutAI::add(entry * val) {
	ExpVector<entry*> * vec = (*_hashes)[val->hash & HASH_MASK];
	if (vec == NULL)
		vec = new ExpVector<entry*>();
	vec->add(val);

	_count++;
	if (val->hash == 116621246993562) {
		std::cout << "116621246993562 added \n";
	}
#if defined(PRINT_COUNT)
	if (_count % PRINT_GRANULARITY == 0)
		std::cout << _count << "\n";
#endif
#if defined(PRINT_ADDED_HASHES)
	std::cout << val->hash << "\n";
#endif
}

sint8 NegaScoutAI::negaScout(State * state, hashcode quickhash, uint8 depth, sint8 alpha, sint8 beta, sint8 color) {

	entry * e = get(quickhash);
	if (e != NULL && e->depth >= depth)
		//if (e != NULL)
		return color * e->eval;

	sint8 score = 0;
	bool quickReturn = false;

	if (depth == 0) {
		score = evaluate(state);
		quickReturn = true;
	}
	if (state->isTerminal()) {
		score = state->utility();
		quickReturn = true;
	}

	if (quickReturn) {
		if (e == NULL) {
			e = new entry();
			e->depth = depth;
			e->eval = score;
			e->hash = quickhash;
			add(e);
		}
		else {
			e->eval = score;
			e->depth = depth;
		}
		return color * score;
	}

	sint8 _alpha = alpha;
	hashcode child_hash = 0;
	ExpVector<Action> * actions = state->getActions();
	State * child = NULL;
	for (uint8 i = 0; i < actions->getLogicSize(); i++) {

		child = state->result(actions->get(i));
		child_hash = _hasher->quickHash(state, actions->get(i), quickhash);
		if(i != 0) {
			score = -negaScout(child, child_hash, depth - 1, -_alpha - 1, -_alpha, -color);
			if (score > _alpha && score < beta)
				score = -negaScout(child, child_hash, depth - 1, -beta, -score, -color);
		}
		else
			score = -negaScout(child, child_hash, depth - 1, -beta, -_alpha, -color);
		delete child;

		_alpha = (_alpha > score) ? _alpha : score;
		if (_alpha >= beta)
			break;
	}
	delete actions;

	if (e == NULL) {
		e = new entry();
		e->depth = depth;
		e->eval = color * _alpha;
		e->hash = quickhash;
		add(e);
	}
	else {
		e->eval = color * _alpha;
		e->depth = depth;
	}

	return _alpha;

}

NegaScoutAI::NegaScoutAI() {
	_hashes = NULL;
	_hasher = ZobristHashing::getInstance();
	_count = 0;
	_depth = DEPTH;
}

uint8 NegaScoutAI::getDepth() {
	return _depth;
}

void NegaScoutAI::setDepth(uint8 depth) {
	_depth = depth;
}

Action NegaScoutAI::choose(State * state) {

	/*	if (state->getPawnsToPlay(state->getPlayer()) == 9)
		return Action(POS_NULL, NEW_POS(2,2,1), POS_NULL); */

	_hashes = new std::vector<ExpVector<entry*>*>(HASH_MASK + 1);
	_count = 0;

	for (int i = 0; i < HASH_MASK + 1; i++)
		(*_hashes)[i] = new ExpVector<entry*>();

	ExpVector<Action> * actions = state->getActions();

	Action res;
	sint8 score;
	entry * tempscore;
	hashcode quickhash, hash;

	hash = _hasher->hash(state);

	if (state->getPlayer() == PAWN_WHITE) {
		negaScout(state, hash, _depth + 1, -(PLAYER_WHITE_UTILITY + 1), -(PLAYER_BLACK_UTILITY - 1), 1);
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			quickhash = _hasher->quickHash(state, actions->get(i), hash);
			tempscore = get(quickhash);
			if (tempscore != NULL) {
				if (i == 0 || tempscore->eval > score) {
					score = tempscore->eval;
					res = actions->get(i);
				}
			}
			else {
				std::cout << "HASH " << quickhash << " not found\n";
				res = actions->get(0);
			}
		}
	}
	else {
		negaScout(state, hash, _depth + 1, -(PLAYER_WHITE_UTILITY + 1), -(PLAYER_BLACK_UTILITY - 1), -1);
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			quickhash = _hasher->quickHash(state, actions->get(i), hash);
			tempscore = get(quickhash);
			if (tempscore != NULL) {
				if (i == 0 || tempscore->eval < score) {
					score = tempscore->eval;
					res = actions->get(i);
				}
			}
			else {
				std::cout << "HASH " << quickhash << " not found\n";
				res = actions->get(0);
			}
		}
	}

	std::cout << _count << "\n";

	delete actions;

	for (int i = 0; i < HASH_MASK + 1; i++)
		if ((*_hashes)[i] != NULL) {
			for (int j = 0; j < (*_hashes)[i]->getLogicSize(); j++)
				delete (*_hashes)[i]->get(j);
			delete (*_hashes)[i];
		}
	delete _hashes;

	return res;
}

NegaScoutAI::~NegaScoutAI() {
	delete _hasher;
}

