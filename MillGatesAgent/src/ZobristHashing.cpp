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
		instance = new ZobristHashing;
	return instance;
}

ZobristHashing::ZobristHashing() {

	for (uint8 i = 0; i < HASH_TABLE_WIDTH; i++)
		for (uint8 j = 0; j < HASH_TABLE_HEIGHT; j++)
			_table[i][j] = rand();

}

int ZobristHashing::hash(State * state) const {

	int hash = 0;
	int j = 0;

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
			for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
				if ((j = state->getPawnAt(x, y, z)) != PAWN_NONE) {
					j = (j == PAWN_WHITE) ? HASH_PAWN_WHITE : HASH_PAWN_BLACK;
					hash ^= _table[x * CUBE_SIZE_Y * CUBE_SIZE_Z + y * CUBE_SIZE_Z + z][j];
				}
	return hash;
}

int ZobristHashing::quickHash(State * state, Action action, int previousHash) const {

	uint8 pos;
	uint8 j;
	uint8 i;
	int h = previousHash;
	pos = action.getSrc();
	if (IS_VALID(pos)) {
		i = GETX(pos) * CUBE_SIZE_Y * CUBE_SIZE_Z + GETY(pos) * CUBE_SIZE_Z + GETZ(pos);
		j = (state->getPlayer() == PAWN_WHITE ? HASH_PAWN_WHITE : HASH_PAWN_BLACK);
		h ^= _table[i][j];
	}
	pos = action.getDest();
	if (IS_VALID(pos)) {
		i = GETX(pos) * CUBE_SIZE_Y * CUBE_SIZE_Z + GETY(pos) * CUBE_SIZE_Z + GETZ(pos);
		j = (state->getPlayer() == PAWN_WHITE ? HASH_PAWN_WHITE : HASH_PAWN_BLACK);
		h ^= _table[i][j];
	}
	pos = action.getRemovedPawn();
	if (IS_VALID(pos)) {
		i = GETX(pos) * CUBE_SIZE_Y * CUBE_SIZE_Z + GETY(pos) * CUBE_SIZE_Z + GETZ(pos);
		j = (OPP(state->getPlayer()) == PAWN_WHITE ? HASH_PAWN_WHITE : HASH_PAWN_BLACK);
		h ^= _table[i][j];
	}

	return h;
}

ZobristHashing::~ZobristHashing() {
	// TODO Auto-generated destructor stub
}

