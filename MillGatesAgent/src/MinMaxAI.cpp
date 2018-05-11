/*
 * MinMaxAI.cpp
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#include "MinMaxAI.h"
//#define PRINT_TREE
#define PRINT_COUNT
#define LEVEL 5
#define PRINT_GRANULARITY 10000

MinMaxAI::MinMaxAI() {
	_hashes = NULL;
	_hasher = ZobristHashing::getInstance();
	_count = 0;
}

bool MinMaxAI::visited(hashcode hash) {
	ExpVector<hashcode> * vec = (*_hashes)[hash & HASH_MASK];
	for (int i = 0; i < vec->getLogicSize(); i++)
		if (vec->get(i) == hash)
			return true;
	return false;
}

void MinMaxAI::add(hashcode hash) {
	ExpVector<hashcode> * vec = (*_hashes)[hash & HASH_MASK];
	if (vec == NULL)
		vec = new ExpVector<hashcode>();
	vec->add(hash);

	_count++;
#if !defined(PRINT_TREE) && defined(PRINT_COUNT)
	if (_count % PRINT_GRANULARITY == 0)
		std::cout << _count << "\n";
#endif
}

int MinMaxAI::evaluate(State * state) {
	int white = state->getPawnsOnBoard(PAWN_WHITE) + state->getPawnsToPlay(PAWN_WHITE);
	int black = state->getPawnsOnBoard(PAWN_BLACK) + state->getPawnsToPlay(PAWN_BLACK);

	return white - black;
}

int MinMaxAI::min(State * state, hashcode hash, int level) {

	add(hash);

	if (state->isTerminal())
		return state->utility();

	if (level >= LEVEL)
		return evaluate(state);

	int min_value = 0;
	hashcode quickhash = 0;
	int utility = 0;
	ExpVector<Action> * actions = state->getActions();

	for (uint8 i = 0; i < actions->getLogicSize(); i++) {
		quickhash = _hasher->quickHash(state, actions->get(i), hash);
		State * res = state->result(actions->get(i));
		utility = 0;
#if defined(PRINT_TREE)
		for (int i = 0; i <= level; i++)
			std::cout << "  ";
		std::cout << actions->get(i) << "{\n";
#endif
		if (!visited(quickhash))
			utility = max(res, quickhash, level + 1);
		else
			utility = evaluate(res);
		delete res;
#if defined(PRINT_TREE)
		for (int i = 0; i <= level; i++)
			std::cout << "  ";
		std::cout << "} = " << utility << "\n";
#endif
		if (i == 0 || utility < min_value)
			min_value = utility;
	}
	delete actions;

	return min_value;
}

int MinMaxAI::max(State * state, hashcode hash, int level) {

	add(hash);

	if (state->isTerminal())
		return state->utility();

	if (level >= LEVEL)
		return evaluate(state);

	int max_value = 0;
	hashcode quickhash = 0;
	int utility = 0;
	ExpVector<Action> * actions = state->getActions();

	for (uint8 i = 0; i < actions->getLogicSize(); i++) {
		quickhash = _hasher->quickHash(state, actions->get(i), hash);
		State * res = state->result(actions->get(i));
		utility = 0;
#if defined(PRINT_TREE)
		for (int i = 0; i <= level; i++)
			std::cout << "  ";
		std::cout << actions->get(i) << "{\n";
#endif
		if (!visited(quickhash))
			utility = min(res, quickhash, level + 1);
		else
			utility = evaluate(res);
		delete res;
#if defined(PRINT_TREE)
		for (int i = 0; i <= level; i++)
			std::cout << "  ";
		std::cout << "} = " << utility << "\n";
#endif
		if (i == 0 || utility > max_value)
			max_value = utility;

	}

	delete actions;

	return max_value;
}

Action MinMaxAI::choose(State * state) {

	_hashes = new std::vector<ExpVector<hashcode>*>(HASH_MASK + 1);
	_count = 0;

	for (int i = 0; i < HASH_MASK + 1; i++)
		(*_hashes)[i] = new ExpVector<hashcode>();

	ExpVector<Action> * actions = state->getActions();
	ExpVector<int> * minMax = new ExpVector<int>();
	State * state_result;
	Action action_result;

	int minMax_value;
	int utility;
	uint8 minMax_index = 0;

	if (state->getPlayer() == PAWN_WHITE) {
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			state_result = state->result(actions->get(i));
#if defined(PRINT_TREE)
			std::cout << actions->get(i) << "{\n";
#endif
			utility = min(state_result, _hasher->hash(state_result), 0);
			minMax->add(utility);
#if defined(PRINT_TREE)
			std::cout << "} = " << utility << "\n";
#endif
			delete state_result;
		}

		minMax_value = minMax->get(0);

		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			if (minMax->get(i) > minMax_value) {
				minMax_value = minMax->get(i);
				minMax_index = i;
			}
		}
	}
	else {
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			state_result = state->result(actions->get(i));
#if defined(PRINT_TREE)
			std::cout << actions->get(i) << "{\n";
#endif
			utility = max(state_result, _hasher->hash(state_result), 0);
			minMax->add(utility);
#if defined(PRINT_TREE)
			std::cout << "} = " << utility << "\n";
#endif
			delete state_result;
		}

		minMax_value = minMax->get(0);

		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			if (minMax->get(i) < minMax_value) {
				minMax_value = minMax->get(i);
				minMax_index = i;
			}
		}
	}

	action_result = actions->get(minMax_index);

	std::cout << _count << "\n";

	delete actions;
	delete minMax;

	for (int i = 0; i < HASH_MASK + 1; i++)
		if ((*_hashes)[i] != NULL)
			delete (*_hashes)[i];
	delete _hashes;

	return action_result;
}

MinMaxAI::~MinMaxAI() {
	delete _hasher;
}

