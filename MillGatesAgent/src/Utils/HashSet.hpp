/*
 * TranspositionTable.cpp
 *
 *  Created on: May 13, 2018
 *      Author: Luca
 */

#include "HashSet.h"

template <class T>
HashSet<T>::HashSet() {
	_table = new std::vector<ExpVector<HashSetEntry<T>*>*>(HASH_MASK + 1);
	for (int i = 0; i < HASH_MASK + 1; i++)
		(*_table)[i] = NULL;
}

template <class T>
bool HashSet<T>::get(hashcode hashcode, T ** val) {
	ExpVector<HashSetEntry<T>*> * vec = (*_table)[hashcode & HASH_MASK];
	if (vec != NULL) {
		for (int i = 0; i < vec->getLogicSize(); i++) {
			if (vec->get(i)->hash == hashcode) {
				*val = &(vec->get(i)->value);
				return true;
			}
		}
	}
	*val = NULL;
	return false;
}

template <class T>
void HashSet<T>::add(hashcode hash, T val) {
	ExpVector<HashSetEntry<T>*> * vec = (*_table)[hash & HASH_MASK];
	if (vec == NULL) {
		vec = new ExpVector<HashSetEntry<T>*>();
		(*_table)[hash & HASH_MASK] = vec;
	}
	HashSetEntry<T> * toAdd = new HashSetEntry<T>();
	toAdd->hash = hash;
	toAdd->value = val;
	vec->add(toAdd);
}

template <class T>
bool HashSet<T>::contains(hashcode hashcode) {
	ExpVector<HashSetEntry<T>*> * vec = (*_table)[hashcode & HASH_MASK];
	if (vec != NULL) {
		for (int i = 0; i < vec->getLogicSize(); i++) {
			if (vec->get(i)->hash == hashcode)
				return true;
		}
	}
	return false;
}

template <class T>
void HashSet<T>::clear() {
	for (int i = 0; i < HASH_MASK + 1; i++)
		if ((*_table)[i] != NULL) {
			for (int j = 0; j < (*_table)[i]->getLogicSize(); j++)
				delete (*_table)[i]->get(j);
			delete (*_table)[i];
			(*_table)[i] = NULL;
		}
}

template <class T>
HashSet<T>::~HashSet() {
	clear();
	delete _table;
}

