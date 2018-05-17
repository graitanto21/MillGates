/*
 * TranspositionTable.h
 *
 *  Created on: May 13, 2018
 *      Author: Luca
 */

#ifndef UTILS_HASHSET_H_
#define UTILS_HASHSET_H_

#include "../Commons.h"
#include "../Domain/State.h"
#include "ExpVector.h"

template <class T> struct HashSetEntry {
	hashcode hash;
	T value;
};

template <class T> class HashSet {
private:

	std::vector<ExpVector<HashSetEntry<T>*>*> * _table;

public:
	HashSet();

	virtual bool get(hashcode hash, T ** ret);
	virtual void add(hashcode hash, T entry);
	virtual bool contains(hashcode hashcode);
	virtual void clear();

	virtual ~HashSet();
};

#include "HashSet.hpp"

#endif /* UTILS_HASHSET_H_ */
