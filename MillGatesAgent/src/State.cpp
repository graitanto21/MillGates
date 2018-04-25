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

State::State(char*stringFromServer) : State() {
	/* Here, state is created (I call the void constructor)
	 * with all position void. Now, I only need to receive
	 * the positions and the content of all the cells
	 * in the format '<x><y><PAWN>'.
	 * Last three chars of the string indicates the number
	 * of pawns of each kind present on the board and the
	 * current phase.
	*/
	int _l = strlen(stringFromServer);
	int i=0;

	//Pawns
	while(i<(_l-3)) {
		setPawnAt(
			/* x */			stringFromServer[i++],
			/* y */ 		stringFromServer[i++],
			/* CONTENT */ 	stringFromServer[i++]);
	}

	// Three last chars
	setWhiteCheckersOnBoard(stringFromServer[i++]);
	setBlackCheckersOnBoard(stringFromServer[i++]);
	setPhase(stringFromServer[i]);
}

// Following are methods for Jack's mapping

//void State::putLeftFace(unsigned int count, char value){
//	//printf("Creating LeftFace...\n");
//	int i = 2 - count % 3;
//	int j = 0;
//	int k = 2 - count/3;
//	printf("%d %d %d left\n", i,j,k);
//	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
//}
//
//void State::putMiddleLine(unsigned int count, char value){ //TODO migliorare per inserire casella al centro
//	int i = count <= 11 ? 2 : 0;
//	int j = 1;
//	int k = count <= 11 ? 11 - count : count - 12;
//	printf("%d %d %d center\n", i,j,k);
//	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
//}
//
//void State::putRightFace(unsigned int count, char value){
//	int i = 2 - count % 3;
//	int j = 2;
//	int k = count/3 - 5;
//	printf("%d %d %d right\n", i,j,k);
//	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
//}
//
//void State::printLeftFace(){
//	int j = 0;
//	for(int i=0; i<=2; i++){
//		for(int k = 2; k >= 0; k--)
//			printf("%d ", pawns[i][j][k]);
//		printf("\n");
//	}
//}
//
//void State::printMiddleLine(){
//	int j=1;
//	int i=0;
//	int k;
//	for(k=2; k>=0; k--)
//		printf("%d\n", pawns[i][j][k]);
//	i = 2;
//	for(k=0; k<=2; k++)
//		printf("%d\n", pawns[i][j][k]);
//}
//
//void State::printRightFace(){
//	int j = 2;
//	for(int i=0; i<=2; i++){
//		for(int k = 0; k <=2; k++)
//			printf("%d ", pawns[i][j][k]);
//		printf("\n");
//	}
//}

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
	int i, j, k;
	i = j = k = -1;

	if ( x == 'd') { // 'd'
		//Coordinate 'x'
		j = 1;
		//Coordinate 'y'
		if ( y > 0 && y < 4) {
			i = 2;
			k =  3 - y;
		}
		else if ( y == 4) {
			i = 1;
			k = 1;
		}
		else if (y > 4 && y < 8) {
			i = 0;
			k = y % 5;
		}
		else return false;
	}
	else {
		//Coordinate 'x'
		if (x >= 'a' && (x/100) == 0) { // 'a','b','c'
		j = 0;
		k = 2 - (x % 'a');
		}
		else if (x <= 'g' && (x/100) == 1) { // 'e','f','g'
			j = 2;
			k = x % 'e';
		} else return false;

		//Coordinate 'y'
		if ( y > 0 && y < 4 )
			i = 2;
		else if ( y == 4)
			i = 1;
		else if (y > 4 && y < 8)
			i = 0;
		else return false;
	}

	if (i<0 || j<0 || k<0)
		return false;

	pawns[i][j][k] = value;
	return true;
}

// If coordinate is not valid, returns -1;
pawn State::getPawnAt(int8 x, int8 y){
	int i, j, k;
		i = j = k = -1;

		if ( x == 'd') { // 'd'
			//Coordinate 'x'
			j = 1;
			//Coordinate 'y'
			if ( y > 0 && y < 4) {
				i = 2;
				k =  3 - y;
			}
			else if ( y == 4) {
				i = 1;
				k = 1;
			}
			else if (y > 4 && y < 8) {
				i = 0;
				k = y % 5;
			}
			else return -1;
		}
		else {
			//Coordinate 'x'
			if (x >= 'a' && (x/100) == 0) { // 'a','b','c'
			j = 0;
			k = 2 - (x % 'a');
			}
			else if (x <= 'g' && (x/100) == 1) { // 'e','f','g'
				j = 2;
				k = x % 'e';
			} else return -1;

			//Coordinate 'y'
			if ( y > 0 && y < 4 )
				i = 2;
			else if ( y == 4)
				i = 1;
			else if (y > 4 && y < 8)
				i = 0;
			else return -1;
		}

		if (i<0 || j<0 || k<0)
			return -1;

		return pawns[i][j][k];
}

void State::setPhase(int8 currentPhase) {
	phase = currentPhase;
}
int8 State::getPhase() {
	return phase;
}

void State::setWhiteCheckersOnBoard(int8 number){
	pawns[1][1][2] = number;
}
int8 State::getWhiteCheckersOnBoard() {
	return pawns[1][1][2];
}

void State::setBlackCheckersOnBoard(int8 number) {
	pawns[1][1][1] = number;
}
int8 State::getBlackCheckersOnBoard() {
	return pawns[1][1][1];
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

//int main(int argc, char **argv) {
//	printf("Program started...\n");
//
//	char * c = "WB0WB00WB0WW0B0WB0BW0WB0\0";
//
//	printf("State String created...\n");
////	State state = *(new State(c));
////	//printf("%s\n", state.toString());
////	printf("\n");
////	state.printLeftFace();
////	state.printMiddleLine();
////	state.printRightFace();
////
////	state.toStringToSend();
////	printf("\n%s\n", c);
//
//	State s;
////	printf("%s\n", s.toString());
//	s.toStringToSend();
//	printf("\n");
//
//	Here some tests
//	s.setPawnAt('a', 1, 'W');
//	s.setPawnAt('c', 5, 'B');
//	s.setPawnAt('d', 4, 'W');
////	printf("%s\n", s.toString());
//	s.toStringToSend();
//
//}


