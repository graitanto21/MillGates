/*
 * MinMaxAI.cpp
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#include "MinMaxAI.h"

MinMaxAI::MinMaxAI() {
	_hashes = new std::vector<bool>(16777216);
	_hasher = ZobristHashing::getInstance();
	_count = 0;
}

int MinMaxAI::min(State * state, hashcode hashcode) {

	if (state->isTerminal())
		return state->utility();

	(*_hashes)[hashcode] = true;
	_count++;
	if (_count % 100 == 0)
		std::cout << _count << "\n";

	int min_value = 0;
	int quickhash = 0;
	int utility;
	ExpVector<Action> * actions = state->getActions();

	for (uint8 i = 0; i < actions->getLogicSize(); i++) {
		quickhash = _hasher->quickHash(state, actions->get(i), hashcode) & 16777215;
		if ((*_hashes)[quickhash] == false) {
			State * res = state->result(actions->get(i));
			utility = max(res, quickhash);
			if (i == 0 || utility < min_value)
				min_value = utility;

			delete res;
		}
	}
	delete actions;

	return min_value;
}

int MinMaxAI::max(State * state, hashcode hashcode) {

	if (state->isTerminal())
		return state->utility();

	(*_hashes)[hashcode] = true;
	_count++;
	if (_count % 100 == 0)
		std::cout << _count << "\n";

	int max_value = 0;
	int quickhash = 0;
	int utility;
	ExpVector<Action> * actions = state->getActions();

	for (uint8 i = 0; i < actions->getLogicSize(); i++) {
		quickhash = _hasher->quickHash(state, actions->get(i), hashcode) & 16777215;
		if ((*_hashes)[quickhash] == false) {
			State * res = state->result(actions->get(i));
			utility = min(res, quickhash);
			if (i == 0 || utility > max_value)
				max_value = utility;
			delete res;
		}
	}

	delete actions;

	return max_value;
}

Action MinMaxAI::choose(State * state) {

	delete _hashes;
	_hashes = new std::vector<bool>(16777216);
	_count = 0;
	for (int i = 0; i < 16777216; i++)
		(*_hashes)[i] = false;

	ExpVector<Action> * actions = state->getActions();
	ExpVector<int> * minMax = new ExpVector<int>();
	State * state_result;
	Action action_result;

	int minMax_value;
	uint8 minMax_index = 0;

	if (state->getPlayer() == PAWN_WHITE) {
		for (uint8 i = 0; i < actions->getLogicSize(); i++) {
			state_result = state->result(actions->get(i));
			minMax->add(min(state_result, _hasher->hash(state_result) & 16777215));
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
			minMax->add(max(state_result, _hasher->hash(state_result) & 16777215));
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

	delete actions;
	delete minMax;

	return action_result;
}

MinMaxAI::~MinMaxAI() {

}

