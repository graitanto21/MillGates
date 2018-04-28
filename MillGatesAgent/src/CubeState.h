/*
 * CubeState.h
 *
 *  Created on: 26 apr 2018
 *      Author: Lorenzo Rosa
 */

#ifndef CUBESTATE_H_
#define CUBESTATE_H_

#include "Commons.h"
#include <iostream>
#include <string>

class CubeState {

public:

	//Getters and setters

	//2D (concrete mapping calling abstract 3D getters/setters).
	virtual bool setPawnAt2D(int8 x, int8 y, pawn value);
	// If coordinate is not valid, returns -1;
	virtual pawn getPawnAt2D(int8 x, int8 y) const;

	//3D (abstract)
	virtual pawn getPawnAt(int8 x, int8 y, int8 z) const = 0;
	virtual void setPawnAt(int8 x, int8 y, int8 z, pawn value) = 0;

	virtual void setPhase(int8 value) = 0;
	virtual int8 getPhase() const = 0;

	virtual void setWhiteCheckersOnBoard(std::string number);
	virtual int8 getWhiteCheckersOnBoard();

	virtual void setBlackCheckersOnBoard(std::string number);
	virtual int8 getBlackCheckersOnBoard();

	//Utiliy methods
	virtual CubeState* clone();
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

	virtual ~CubeState();
};

// For printing a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const CubeState &s);


#endif /* CUBESTATE_H_ */
