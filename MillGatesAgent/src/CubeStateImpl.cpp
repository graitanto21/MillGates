/*
 * CubeStateImpl.cpp
 *
 *  Created on: 28 apr 2018
 *      Author: Lorenzo Rosa
 */

#include "CubeStateImpl.h"

//Constructors

CubeStateImpl::CubeStateImpl() {
	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)
				pawns[i][j][k] = PAWN_NONE;

	phase = PHASE_1;
	setPawnsOnBoard(PAWN_WHITE, 0);
	setPawnsOnBoard(PAWN_BLACK, 0);
}

CubeStateImpl::CubeStateImpl(std::string stringFromServer) : CubeStateImpl() {
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
		setPawnAt2D(
				/* x */			(int8)stringFromServer[i],
				/* y */ 		(int8)stringFromServer[i+1],
				/* CONTENT */ 	(int8)stringFromServer[i+2]);
		i+=3;
	}
	setWhitePawnsOnBoardStr(stringFromServer.substr(i, 2));
	setBlackPawnsOnBoardStr(stringFromServer.substr(i+2, 2));
	setPhase(stringFromServer[i+4]);
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

//Getters and setters
void CubeStateImpl::setPawnAt(int8 x, int8 y, int8 z, pawn value) {
	pawns[x][y][z] = value;
}
pawn CubeStateImpl::getPawnAt(int8 x, int8 y, int8 z) const {
	return pawns[x][y][z];
}

void CubeStateImpl::setPhase(int8 currentPhase) {
	phase = currentPhase;
}
int8 CubeStateImpl::getPhase() const {
	return phase;
}

State * CubeStateImpl::clone() {

	State * clone = new CubeStateImpl();

	for (int i = 0; i < CUBE_SIZE_X; i++)
		for (int j = 0; j < CUBE_SIZE_Y; j++)
			for (int k = 0; k < CUBE_SIZE_Z; k++)
				clone->setPawnAt(i, j, k, getPawnAt(i, j, k));

	clone->setPhase(getPhase());
	clone->setWhitePawnsOnBoardStr(getWhitePawnsOnBoardStr() + "");
	clone->setBlackPawnsOnBoardStr(getBlackPawnsOnBoardStr() + "");

	return clone;
}

CubeStateImpl::~CubeStateImpl() {}

//int main(int argc, char **argv) {
//	printf("Program started...\n");
//
//	//Create a state from string
//	std::string str("a1Oa4Oa7Wb2Bb4Wb6Bc3Wc4Bc5Wd1Wd2Od3Od5Od6Od7Oe3Oe4Oe5Of2Wf4Wf6Bg1Og4Wg7O10101"); //created string
//	CubeStateImpl s_from_string(str);
//	std::cout << "State  created from string (internal repr): " << s_from_string << "\n";
//	std::cout << "State  created from string (ordered repr): ";
//	s_from_string.toStringToSend();
//	std::cout << "\n";
//
//	//Create a void state
//	CubeStateImpl s_void;
//	std::cout << "State created void: " << s_void << "\n";
//
//	//Here some tests
//	s_void.setPawnAt2D('a', '1', 'W');
//	s_void.setPawnAt2D('c', '5', 'B');
//	s_void.setPawnAt2D('d', '4', 'W'); //This is the center: the ordered view does not see it!
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


