/*
 * ZobristHashing.h
 *
 *  Created on: May 8, 2018
 *      Author: Luca
 */

#ifndef ZOBRISTHASHING_H_
#define ZOBRISTHASHING_H_

#include "Commons.h"
#include "State.h"
#include <stdlib.h>

class ZobristHashing {
private:
	hashcode _table[HASH_TABLE_WIDTH][HASH_TABLE_HEIGHT];
	static ZobristHashing * instance;
	ZobristHashing();

public:

	static ZobristHashing * getInstance();
	hashcode hash(State * state) const;

	hashcode quickHash(State * state, Action action, hashcode previousHash) const;

	virtual ~ZobristHashing();
};

#endif /* ZOBRISTHASHING_H_ */
