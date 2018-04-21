/*
 * State.h
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#ifndef STATE_H_
#define STATE_H_

#include "Commons.h"

class State {

	pawn pawns[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
	int8 phase;

public:

	State();
	State * clone();

	pawn * getPawns();
	pawn getPawnAt(int8 x, int8 y, int8 z);
	int8 getPhase();

	void setPawnAt(int8 x, int8 y, int8 z, pawn value);
	//bool setPawnAt(int8 x, int8y, pawn value);
	void setPhase(int8 value);

	char * toString();

	virtual ~State();

};

#endif /* STATE_H_ */
