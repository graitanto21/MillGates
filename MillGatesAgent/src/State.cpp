/*
 * State.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#include "State.h"

State::State() {

	for (int i = 0; i < CUBE_SIZE; i++)
		for (int j = 0; j < CUBE_SIZE; j++)
			for (int k = 0; k < CUBE_SIZE; k++)

				pawns[i][j][k] = PAWN_NONE;

	phase = PHASE_1;

}

State * State::clone() {

	State * res = new State();

	for (int i = 0; i < CUBE_SIZE; i++)
		for (int j = 0; j < CUBE_SIZE; j++)
			for (int k = 0; k < CUBE_SIZE; k++)

				res->setPawnAt(i, j, k, getPawnAt(i, j, k));

	res->setPhase(getPhase());

	return res;

}

void State::setPawnAt(int8 x, int8 y, int8 z, pawn value) {

	pawns[x][y][z] = value;

}

void State::setPhase(int8 value) {

	phase = value;

}

pawn State::getPawnAt(int8 x, int8 y, int8 z) {

	return pawns[x][y][z];

}

int8 State::getPhase() {

	return phase;

}

char * State::toString() {

	static char res[CUBE_SIZE * 3];

	for (int i = 0; i < CUBE_SIZE; i++)
		for (int j = 0; j < CUBE_SIZE; j++)
			for (int k = 0; k < CUBE_SIZE; k++)

				res[i * CUBE_SIZE*CUBE_SIZE + j * CUBE_SIZE + k] = (pawns[i][j][k] == PAWN_NONE ? '0' : (pawns[i][j][k] == PAWN_BLACK ? 'B' : 'W'));

	return res;

}

State::~State() {
	// TODO Auto-generated destructor stub
}

