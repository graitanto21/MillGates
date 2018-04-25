/*
 * State.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#include "State.h"
#include "string.h"
#include "stdio.h"

//Constructors
State::State() {

	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)

				pawns[i][j][k] = PAWN_NONE;

	phase = PHASE_1;

}

/*
7 O--------O--------O
6 |--O-----O-----O--|
5 |--|--O--O--O--|--|
4 O--O--O     O--O--O
3 |--|--O--O--O--|--|
2 |--O-----O-----O--|
1 O--------O--------O
  a  b  c  d  e  f  g
 */

State::State(char *stringFromServer) : State() {
	for(unsigned int count = 0; count <= strlen(stringFromServer) - 1; count++){
		if (count <= 8){
			putLeftFace(count, stringFromServer[count]);
		}
		else if (9 <= count and count <= 14) //TODO migliorare per inserire cella al centro
			putMiddleLine(count, stringFromServer[count]);
		else
			putRightFace(count, stringFromServer[count]);

	}
}

void State::putLeftFace(unsigned int count, char value){
	//printf("Creating LeftFace...\n");
	int i = 2 - count % 3;
	int j = 0;
	int k = 2 - count/3;
	printf("%d %d %d left\n", i,j,k);
	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
}

void State::putMiddleLine(unsigned int count, char value){ //TODO migliorare per inserire casella al centro
	int i = count <= 11 ? 2 : 0;
	int j = 1;
	int k = count <= 11 ? 11 - count : count - 12;
	printf("%d %d %d center\n", i,j,k);
	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
}

void State::putRightFace(unsigned int count, char value){
	int i = 2 - count % 3;
	int j = 2;
	int k = count/3 - 5;
	printf("%d %d %d right\n", i,j,k);
	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
}

void State::printLeftFace(){
	int j = 0;
	for(int i=0; i<=2; i++){
		for(int k = 2; k >= 0; k--)
			printf("%d ", pawns[i][j][k]);
		printf("\n");
	}
}

void State::printMiddleLine(){
	int j=1;
	int i=0;
	int k;
	for(k=2; k>=0; k--)
		printf("%d\n", pawns[i][j][k]);
	i = 2;
	for(k=0; k<=2; k++)
		printf("%d\n", pawns[i][j][k]);
}

void State::printRightFace(){
	int j = 2;
	for(int i=0; i<=2; i++){
		for(int k = 0; k <=2; k++)
			printf("%d ", pawns[i][j][k]);
		printf("\n");
	}
}

void State::toStringToSend(){
	char ret[25]; //TODO migliorare per inserire la casella al centro
				  //24 + \0

	//Insert left face
	int count = 0;
	int i, j=0, k;

	for(k=2; k>=0; k--)
		for(i=2; i>=0; i--){
			ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
			printf("%c", ret[count - 1]);
		}

	//Insert middle line
	j=1;
	i=2;
	for(k=2; k>=0; k--){
		ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
		printf("%c", ret[count - 1]);
	}
	i=0;
	for(k=0; k<=2; k++){
		ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
		printf("%c", ret[count - 1]);
	}

	//Insert right face
	j=2;
	for(k=0; k<=2; k++)
		for(i=2; i>=0; i--){
			ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
			printf("%c", ret[count - 1]);
		}


	ret[count] = '\0';
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

int main(int argc, char **argv) {
	printf("Program started...\n");
	char * c = "WB0WB00WB0WW0B0WB0BW0WB0\0";
	printf("State String created...\n");
	State state = *(new State(c));
	//printf("%s\n", state.toString());
	printf("\n");
	state.printLeftFace();
	state.printMiddleLine();
	state.printRightFace();

	state.toStringToSend();
	printf("\n%s\n", c);
}


