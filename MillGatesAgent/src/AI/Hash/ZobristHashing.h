/*
 * ZobristHashing.h
 *
 *  Created on: May 8, 2018
 *      Author: Luca
 */

#ifndef AI_HASH_ZOBRISTHASHING_H_
#define AI_HASH_ZOBRISTHASHING_H_

#include "../../Commons.h"
#include <stdlib.h>
#include "../../Domain/State.h"

class ZobristHashing {
private:
	hashcode _table[CUBE_SIZE_X][CUBE_SIZE_Y][CUBE_SIZE_Z][HASH_TABLE_HEIGHT];
	static ZobristHashing * instance;
	ZobristHashing();

public:

	static ZobristHashing * getInstance();
	hashcode hash(State * state) const;

	hashcode quickHash(State * state, Action action, hashcode previousHash) const;

	virtual ~ZobristHashing();
};

#endif /* AI_HASH_ZOBRISTHASHING_H_ */
