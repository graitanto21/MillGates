/*
 * State.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#include "State.h"

//Constructors
State::State() {

	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)

				pawns[i][j][k] = PAWN_NONE;

	phase = PHASE_1;

}
State::State(char*stringFromServer) : State() {
	//TODO Insert, for a string representation, the pawn in the board
}

//Getters and setters
void State::setPawnAt(int x, int y, int z, pawn value) {
	pawns[x][y][z] = value;
}
pawn State::getPawnAt(int x, int y, int z) {
	return pawns[x][y][z];
}

bool State::setPawnAt(int8 x, int8 y, pawn value){
	//TODO Mapping function!
	return false;
}
pawn State::getPawnAt(int8 x, int8 y){
	//TODO Mapping function!
	return NULL;
}

void State::setPhase(int8 currentPhase) {
	phase = currentPhase;
}
int8 State::getPhase() {
	return phase;
}

void setWhiteCheckersOnBoard(){
	//TODO: using the unused places of the cube!
}
int8 getWhiteCheckersOnBoard() {
	//TODO: using the unused places of the cube!
	return 0;
}

void setBlackCheckersOnBoard() {
	//TODO: using the unused places of the cube!
}
int8 getBlackCheckersOnBoard() {
	//TODO: using the unused places of the cube!
	return NULL;
}

//Utiliy methods
State* State::clone() {

	State * res = new State();

	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)

				res->setPawnAt(i, j, k, getPawnAt(i, j, k));

	res->setPhase(getPhase());

	return res;

}

char* State::toString() {

	static char res[CUBE_SIZE_X*CUBE_SIZE_Y*CUBE_SIZE_Z];

	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)

				res[i * CUBE_SIZE_X*CUBE_SIZE_Y + j * CUBE_SIZE_Z + k] = (pawns[i][j][k] == PAWN_NONE ? '0' : (pawns[i][j][k] == PAWN_BLACK ? 'B' : 'W'));

	return res;

}

int State::hash() {
	//TODO
	return 0;
}

State::~State() {}

