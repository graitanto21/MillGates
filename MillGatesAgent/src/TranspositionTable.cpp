/*
 * TranspositionTable.cpp
 *
 *  Created on: May 13, 2018
 *      Author: Luca
 */

#include "TranspositionTable.h"

TranspositionTable::TranspositionTable() {
	_table = new std::vector<ExpVector<entry*>*>(HASH_MASK + 1);
	for (int i = 0; i < HASH_MASK + 1; i++)
		(*_table)[i] = NULL;
}

entry * TranspositionTable::get(hashcode hashcode) {
	ExpVector<entry*> * vec = (*_table)[hashcode & HASH_MASK];
	if (vec != NULL) {
		for (int i = 0; i < vec->getLogicSize(); i++) {
			if (vec->get(i)->hash == hashcode)
				return vec->get(i);
		}
	}
	return NULL;
}

void TranspositionTable::add(entry * val) {
	ExpVector<entry*> * vec = (*_table)[val->hash & HASH_MASK];
	if (vec == NULL) {
		vec = new ExpVector<entry*>();
		(*_table)[val->hash & HASH_MASK] = vec;
	}
	vec->add(val);
}

void TranspositionTable::clear() {
	for (int i = 0; i < HASH_MASK + 1; i++)
		if ((*_table)[i] != NULL) {
			for (int j = 0; j < (*_table)[i]->getLogicSize(); j++)
				delete (*_table)[i]->get(j);
			delete (*_table)[i];
			(*_table)[i] = NULL;
		}
}

TranspositionTable::~TranspositionTable() {
	delete _table;
}

