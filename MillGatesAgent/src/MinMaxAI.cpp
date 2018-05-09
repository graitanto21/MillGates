/*
 * MinMaxAI.cpp
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#include "MinMaxAI.h"

MinMaxAI::MinMaxAI() {
	_hashes = new ExpVector<int>();
	_hasher = ZobristHashing::getInstance();
}

int MinMaxAI::min(State * state) {

	_hashes->add(_hasher->hash(state));
	if (_hashes->getLogicSize() % 1000 == 0)
		std::cout << _hashes->getLogicSize();

	if (state->isTerminal())
		return state->utility();
	for (int i = 0; i < _hashes->getLogicSize(); i++)
		if (_hashes->get(i) == _hasher->hash(state))
			return 0;

	int min_value = 0;
	int utility;
	ExpVector<Action> actions = state->getActions();

	for (uint8 i = 0; i < actions.getLogicSize(); i++) {
		utility = max(state->result(actions.get(i)));
		if (i == 0 || utility < min_value)
			min_value = utility;
	}

	return min_value;
}

int MinMaxAI::max(State * state) {

	_hashes->add(_hasher->hash(state));
	if (_hashes->getLogicSize() % 1000 == 0)
		std::cout << _hashes->getLogicSize();

	if (state->isTerminal())
		return state->utility();
	for (int i = 0; i < _hashes->getLogicSize(); i++)
		if (_hashes->get(i) == _hasher->hash(state))
			return 0;

	int max_value = 0;
	int utility;
	ExpVector<Action> actions = state->getActions();

	for (uint8 i = 0; i < actions.getLogicSize(); i++) {
		utility = min(state->result(actions.get(i)));
		if (i == 0 || utility > max_value)
			max_value = utility;
	}

	return max_value;
}

Action MinMaxAI::choose(State * state) {

	delete _hashes;
	_hashes = new ExpVector<int>();

	ExpVector<Action> actions = state->getActions();
	ExpVector<int> minMax;

	int minMax_value;
	uint8 minMax_index = 0;

	if (state->getPlayer() == PAWN_WHITE) {
		for (uint8 i = 0; i < actions.getLogicSize(); i++)
			minMax.add(min(state->result(actions.get(i))));

		minMax_value = minMax.get(0);

		for (uint8 i = 0; i < actions.getLogicSize(); i++) {
			if (minMax.get(i) > minMax_value) {
				minMax_value = minMax.get(i);
				minMax_index = i;
			}
		}
	}
	else {
		for (uint8 i = 0; i < actions.getLogicSize(); i++)
			minMax.add(max(state->result(actions.get(i))));

		minMax_value = minMax.get(0);

		for (uint8 i = 0; i < actions.getLogicSize(); i++) {
			if (minMax.get(i) < minMax_value) {
				minMax_value = minMax.get(i);
				minMax_index = i;
			}
		}
	}

	return actions.get(minMax_index);
}

MinMaxAI::~MinMaxAI() {

}

