/*
 * CubeState.h
 *
 *  Created on: 26 apr 2018
 *      Author: Lorenzo Rosa
 */

#ifndef CUBESTATE_H_
#define CUBESTATE_H_

#include "State.h"
#include "Commons.h"

class CubeState: public State {
private:
	//Data structures
	pawn pawns[CUBE_SIZE_X][CUBE_SIZE_Y][CUBE_SIZE_Z];
	int8 phase;

	//Getters and setters
	virtual pawn getPawnAt(int x, int y, int z);
	virtual void setPawnAt(int x, int y, int z, pawn value);
//

public:

	//Constructors
	CubeState();
	CubeState(std::string stringFromServer);

	virtual bool setPawnAt(int8 x, int8 y, pawn value);
	// If coordinate is not valid, returns -1;
	virtual pawn getPawnAt(int8 x, int8 y);

	virtual void setPhase(int8 value);
	virtual int8 getPhase() const;

	virtual void setWhiteCheckersOnBoard(std::string number);
	virtual int8 getWhiteCheckersOnBoard();

	virtual void setBlackCheckersOnBoard(std::string number);
	virtual int8 getBlackCheckersOnBoard();

	//Utiliy methods
	virtual State* clone();
	virtual int hash();
	virtual std::string toString() const;

	//For debug
	void toStringToSend();

	//	//For debug
	//	void printLeftFace();
	//	void printMiddleLine();
	//	void printRightFace();
	//
	//	void toStringToSend();
		//private:
	//	//For the mapping
	//	void putLeftFace(unsigned int count, char value);
	//	void putMiddleLine(unsigned int count, char value);
	//	void putRightFace(unsigned int count, char value);
	//
	//	//Testing
	//	void toStringToSend();

	~CubeState();
};

#endif /* CUBESTATE_H_ */
