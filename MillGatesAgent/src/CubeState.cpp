/*
 * CubeState.cpp
 *
 *  Created on: 26 apr 2018
 *      Author: Lorenzo Rosa (lorenzo.rosa.bo@gmail.com)
 */

#include "CubeState.h"
#include <string>
#include <cstdlib>
#include "stdio.h"

//Constructors
CubeState::CubeState() {
	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)
				pawns[i][j][k] = NONE;

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

//CubeState::CubeState(char *stringFromServer) : State() {
//	for(unsigned int count = 0; count <= strlen(stringFromServer) - 1; count++){
//		if (count <= 8){
//			putLeftFace(count, stringFromServer[count]);
//		}
//		else if (9 <= count and count <= 14) //TODO migliorare per inserire cella al centro
//			putMiddleLine(count, stringFromServer[count]);
//		else //cosa  das
//			putRightFace(count, stringFromServer[count]);
//
//	}
//}
//
//void CubeState::putLeftFace(unsigned int count, char value){
//	//printf("Creating LeftFace...\n");
//	int i = 2 - count % 3;
//	int j = 0;
//	int k = 2 - count/3;
//	printf("%d %d %d left\n", i,j,k);
//	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
//}
//
//void CubeState::putMiddleLine(unsigned int count, char value){ // migliorare per inserire casella al centro
//	int i = count <= 11 ? 2 : 0;
//	int j = 1;
//	int k = count <= 11 ? 11 - count : count - 12;
//	printf("%d %d %d center\n", i,j,k);
//	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
//}
//
//void CubeState::putRightFace(unsigned int count, char value){
//	int i = 2 - count % 3;
//	int j = 2;
//	int k = count/3 - 5;
//	printf("%d %d %d right\n", i,j,k);
//	pawns[i][j][k] = value == NONE ? PAWN_NONE : (value == BLACK ? PAWN_BLACK : PAWN_WHITE);
//}
//
//void CubeState::printLeftFace(){
//	int j = 0;
//	for(int i=0; i<=2; i++){
//		for(int k = 2; k >= 0; k--)
//			printf("%d ", pawns[i][j][k]);
//		printf("\n");
//	}
//}
//
//void CubeState::printMiddleLine(){
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
//void CubeState::printRightFace(){
//	int j = 2;
//	for(int i=0; i<=2; i++){
//		for(int k = 0; k <=2; k++)
//			printf("%d ", pawns[i][j][k]);
//		printf("\n");
//	}
//}

//void CubeState::toStringToSend(){
//	char ret[25]; //migliorare per inserire la casella al centro
//				  //24 + \0
//
//	//Insert left face
//	int count = 0;
//	int i, j=0, k;
//
//	for(k=2; k>=0; k--)
//		for(i=2; i>=0; i--){
//			ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
//			printf("%c", ret[count - 1]);
//		}
//
//	//Insert middle line
//	j=1;
//	i=2;
//	for(k=2; k>=0; k--){
//		ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
//		printf("%c", ret[count - 1]);
//	}
//	i=0;
//	for(k=0; k<=2; k++){
//		ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
//		printf("%c", ret[count - 1]);
//	}
//
//	//Insert right face
//	j=2;
//	for(k=0; k<=2; k++)
//		for(i=2; i>=0; i--){
//			ret[count++] = pawns[i][j][k] == PAWN_WHITE ? 'W' : (pawns[i][j][k] == PAWN_NONE ? '0' : 'B');
//			printf("%c", ret[count - 1]);
//		}
//
//
//	ret[count] = '\0';

CubeState::CubeState(std::string stringFromServer) : CubeState() {
	/* Here, state is created (I call the void constructor)
	 * with all position void. Now, I only need to receive
	 * the positions and the content of all the cells
	 * in the format '<x><y><PAWN>'.
	 * Last three chars of the string indicates the number
	 * of pawns of each kind present on the board and the
	 * current phase.
	*/
	unsigned int i=0;
	//Pawns
	while(i<(stringFromServer.length()-5)) {
		setPawnAt(
			/* x */			stringFromServer[i],
			/* y */ 		stringFromServer[i+1],
			/* CONTENT */ 	stringFromServer[i+2]);
		i+=3;
	}
	setWhiteCheckersOnBoard(stringFromServer.substr(i, 2));
	setBlackCheckersOnBoard(stringFromServer.substr(i+2, 2));
	setPhase(stringFromServer[i+4]);
}

//Getters and setters
void CubeState::setPawnAt(int x, int y, int z, pawn value) {
	pawns[x][y][z] = value;
}
pawn CubeState::getPawnAt(int x, int y, int z) {
	return pawns[x][y][z];
}

bool CubeState::setPawnAt(int8 x, int8 y, pawn value){
	int i, j, k;
	i = j = k = -1;

	//Convert from char to int
	y= y - '1' + 1;

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
			k = 0;
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

	setPawnAt(i,j,k, value);
	return true;
}

// If coordinate is not valid, returns -1;
pawn CubeState::getPawnAt(int8 x, int8 y){
	int i, j, k;
		i = j = k = -1;

		//Convert from char to int
		y= y - '1' + 1;

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

		return getPawnAt(i,j,k);
}

void CubeState::setPhase(int8 currentPhase) {
	phase = currentPhase;
}
int8 CubeState::getPhase() const {
	return phase;
}

void CubeState::setWhiteCheckersOnBoard(std::string number){
	setPawnAt(1,1,2,atoi(number.c_str()));
}
int8 CubeState::getWhiteCheckersOnBoard() {
	return getPawnAt(1,1,2) + '1' - 1;
}

void CubeState::setBlackCheckersOnBoard(std::string  number) {
	setPawnAt(1,1,1,atoi(number.c_str()));
}
int8 CubeState::getBlackCheckersOnBoard() {
	return getPawnAt(1,1,1) + '1' - 1;
}

//Utiliy methods
State* CubeState::clone() {
	//TODO
//
//	CubeState * res = new CubeState();
//
//	for (int i = 0; i < CUBE_SIZE_X; i++)
//		for (int j = 0; j < CUBE_SIZE_Y; j++)
//			for (int k = 0; k < CUBE_SIZE_Z; k++)
//
//				res->setPawnAt(i, j, k, getPawnAt(i, j, k));
//
//	res->setPhase(getPhase());
//
//	return res;
	return NULL;
}

std::string CubeState::toString() const {

	char res[CUBE_SIZE_X*CUBE_SIZE_Y*CUBE_SIZE_Z + 1];

	int l = 0;
	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++){
				if (i==1 && j==1 && k==1 && pawns[i][j][k] != NONE)
					res[l] = pawns[i][j][k] < 10 ? (pawns[1][1][1] + '0') : 'A' + (pawns[i][j][k]%10);
				else if (i==1 && j==1 && k==2 && pawns[i][j][k] != NONE)
					res[l] = pawns[i][j][k] < 10 ? (pawns[1][1][2] + '0') : 'A' + (pawns[i][j][k]%10);
				else res[l] = pawns[i][j][k];
				l++;
			}
	res[l] = '\0';
	return std::string(res) + '('+ (char)phase+')';

}

int CubeState::hash() {
	//TODO
	return 0;
}

CubeState::~CubeState() {}

void CubeState::toStringToSend(){
	char ret[25]; //TODO migliorare per inserire la casella al centro
				  //24 + \0

	//Insert left face
	int count = 0;
	int i, j=0, k;

	for(k=2; k>=0; k--)
		for(i=2; i>=0; i--){
			ret[count++] = pawns[i][j][k];
			printf("%c", ret[count - 1]);
		}

	//Insert middle line
	j=1;
	i=2;
	for(k=2; k>=0; k--){
		ret[count++] = pawns[i][j][k];
		printf("%c", ret[count - 1]);
	}
	i=0;
	for(k=0; k<=2; k++){
		ret[count++] = pawns[i][j][k];
		printf("%c", ret[count - 1]);
	}

	//Insert right face
	j=2;
	for(k=0; k<=2; k++)
		for(i=2; i>=0; i--){
			ret[count++] = pawns[i][j][k];
			printf("%c", ret[count - 1]);
		}


	ret[count] = '\0';
}

//int main(int argc, char **argv) {
//	printf("Program started...\n");
//
//	//Create a state from string
//	std::string str("a1Oa4Oa7Wb2Bb4Wb6Bc3Wc4Bc5Wd1Wd2Od3Od5Od6Od7Oe3Oe4Oe5Of2Wf4Wf6Bg1Og4Wg7O10101"); //created string
//	CubeState s_from_string(str);
//	std::cout << "State  created from string (internal repr): " << s_from_string << "\n";
//	std::cout << "State  created from string (ordered repr): ";
//	s_from_string.toStringToSend();
//	std::cout << "\n";
//
//	//Create a void state
//	CubeState s_void;
//	std::cout << "State created void: " << s_void << "\n";
//
//	//Here some tests
//	s_void.setPawnAt('a', '1', 'W');
//	s_void.setPawnAt('c', '5', 'B');
//	s_void.setPawnAt('d', '4', 'W'); //This is the center: the ordered view does not see it!
//	s_void.setPhase(PHASE_3);
//
//	s_void.setBlackCheckersOnBoard("10");
//	s_void.setWhiteCheckersOnBoard("11");
//
//	std::cout << "State modified from setters (internal repr): " << s_void << "\n";
//	std::cout << "State  created from string (ordered repr): ";
//	s_void.toStringToSend();
//	std::cout << "\n";
//}
//
