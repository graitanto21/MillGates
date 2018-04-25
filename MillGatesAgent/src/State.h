/*
 * State.h
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#ifndef STATE_H_
#define STATE_H_

#include "Commons.h"
#include <iostream>
#include <string>

class State {
private:

	pawn pawns[CUBE_SIZE_X][CUBE_SIZE_Y][CUBE_SIZE_Z];
	int8 phase;

public:

	//Constructor
	State();
	State(char*stringFromServer);

	//Getters and setters
	pawn getPawnAt(int x, int y, int z);
	void setPawnAt(int x, int y, int z, pawn value);

	bool setPawnAt(int8 x, int8 y, pawn value);

	// If coordinate is not valid, returns -1;
	pawn getPawnAt(int8 x, int8 y);

	void setPhase(int8 value);
	int8 getPhase();

	void setWhiteCheckersOnBoard(int8 number);
	int8 getWhiteCheckersOnBoard();

	void setBlackCheckersOnBoard(int8 number);
	int8 getBlackCheckersOnBoard();

	//Utiliy methods
	State* clone();
	int hash();
	virtual char* toString();
	virtual ~State();

//	//For debug
//	void printLeftFace();
//	void printMiddleLine();
//	void printRightFace();
//
	void toStringToSend();

//private:
//	//For the mapping
//	void putLeftFace(unsigned int count, char value);
//	void putMiddleLine(unsigned int count, char value);
//	void putRightFace(unsigned int count, char value);

};

std::ostream& operator<<(std::ostream &strm, const State &s);


#endif /* STATE_H_ */
