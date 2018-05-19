/*
 * ZobristHashing.cpp
 *
 *  Created on: May 8, 2018
 *      Author: Luca
 */

#include "ZobristHashing.h"

#include <stdlib.h>

ZobristHashing* ZobristHashing::instance = NULL;

ZobristHashing* ZobristHashing::getInstance() {
	if(instance == NULL)
		instance = new ZobristHashing();
	return instance;
}

ZobristHashing::ZobristHashing() {

	unsigned long long h = 0;

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
			for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
				for (uint8 p = 0; p < HASH_TABLE_HEIGHT; p++) {
					h = rand();
					h = (h << 32) | rand();
					_table[x][y][z][p] = (hashcode) h;
				}

}

hashcode ZobristHashing::hash(State * state) const {

	hashcode hash = 0;
	pawn p;

	for (sint8 x = 0; x < CUBE_SIZE_X; x++)
		for (sint8 y = 0; y < CUBE_SIZE_Y; y++)
			for (sint8 z = 0; z < CUBE_SIZE_Z; z++)
				if (POS_ENABLED(x,y) && (p = state->getPawnAt(x, y, z)) != PAWN_NONE) {
					p = (p == PAWN_WHITE) ? HASH_PAWN_WHITE : HASH_PAWN_BLACK;
					hash ^= _table[x][y][z][p];
				}
	return hash;
}

hashcode ZobristHashing::quickHash(State * state, Action action, hashcode previousHash) const {

	Position pos;
	pawn p;
	hashcode h = previousHash;

	p = (state->getPlayer() == PAWN_WHITE ? HASH_PAWN_WHITE : HASH_PAWN_BLACK);
	pos = action.getSrc();
	if (IS_VALID(pos))
		h ^= _table[pos.x][pos.y][pos.z][p];

	pos = action.getDest();
	if (IS_VALID(pos))
		h ^= _table[pos.x][pos.y][pos.z][p];

	p = (state->getPlayer() == PAWN_BLACK ? HASH_PAWN_WHITE : HASH_PAWN_BLACK);
	pos = action.getRemovedPawn();
	if (IS_VALID(pos))
		h ^= _table[pos.x][pos.y][pos.z][p];

	return h;

}

ZobristHashing::~ZobristHashing() {
	// TODO Auto-generated destructor stub
}

