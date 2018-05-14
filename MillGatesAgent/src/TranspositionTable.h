/*
 * TranspositionTable.h
 *
 *  Created on: May 13, 2018
 *      Author: Luca
 */

#ifndef TRANSPOSITIONTABLE_H_
#define TRANSPOSITIONTABLE_H_

#include "ExpVector.h"
#include "State.h"
#include "Commons.h"

typedef struct {
	uint8 depth;
	eval_t eval;
	hashcode hash;
} entry;

class TranspositionTable {
private:

	std::vector<ExpVector<entry*>*> * _table;

public:
	TranspositionTable();

	virtual entry * get(hashcode hashcode);
	virtual void add(entry * entry);
	virtual void clear();

	virtual ~TranspositionTable();
};

#endif /* TRANSPOSITIONTABLE_H_ */
