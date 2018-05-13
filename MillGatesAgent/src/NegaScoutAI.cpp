/*
 * NegaScoutAI.cpp
 *
 *  Created on: May 11, 2018
 *      Author: Luca
 */

#include "NegaScoutAI.h"

#define DEPTH 7

NegaScoutAI::NegaScoutAI() {
	_table = new TranspositionTable();
	_hasher = ZobristHashing::getInstance();
	_depth = DEPTH;
}

sint8 NegaScoutAI::evaluate(State * state) {
	sint8 white = state->getPawnsOnBoard(PAWN_WHITE) + state->getPawnsToPlay(PAWN_WHITE);
	sint8 black = state->getPawnsOnBoard(PAWN_BLACK) + state->getPawnsToPlay(PAWN_BLACK);

	if (white - black > 6 || white - black < -6)
		std::cout << "A NON terminal state has evaluation " << white - black << "\n";

	return white - black;
}

sint8 NegaScoutAI::negaScout(State * state, hashcode quickhash, uint8 depth, sint8 alpha, sint8 beta, sint8 color) {

	entry * e = _table->get(quickhash);
	if (e != NULL && e->depth >= depth)
	//if (e != NULL)
		return color * e->eval;

	sint8 score = 0;
	bool quickReturn = false;

	if (state->isTerminal()) {
		score = state->utility();
		quickReturn = true;
	}
	else if (depth == 0) {
		score = evaluate(state);
		quickReturn = true;
	}

	if (quickReturn) {
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
	State * child = NULL;
	for (uint8 i = 0; i < actions->getLogicSize(); i++) {

		child = state->result(actions->get(i));
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
		if (alpha >= beta)
			break;
	}
	delete actions;

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

Action NegaScoutAI::choose(State * state) {

	/*	if (state->getPawnsToPlay(state->getPlayer()) == 9)
		return Action(POS_NULL, NEW_POS(2,2,1), POS_NULL); */

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
		negaScout(state, hash, _depth + 1, -(PLAYER_WHITE_UTILITY + 1), -(PLAYER_BLACK_UTILITY - 1), -1);
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

NegaScoutAI::~NegaScoutAI() {
	delete _table;
}

