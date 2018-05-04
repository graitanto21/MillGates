/*
 * CubeState.h
 *
 *  Created on: 26 apr 2018
 *      Author: Lorenzo Rosa
 */

#ifndef STATE_H_
#define STATE_H_

#include "Commons.h"
#include "ExpVector.h"
#include <iostream>
#include <string>

class State {

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

	virtual void setWhitePawnsOnBoardStr(std::string number);
	virtual int8 getWhitePawnsOnBoardStr() const;

	virtual void setBlackPawnsOnBoardStr(std::string number);
	virtual int8 getBlackPawnsOnBoardStr() const;

	virtual void setPawnsOnBoard(pawn pawn, int count);
	virtual int8 getPawnsOnBoard(pawn pawn) const;

	//Utility methods
	virtual State* clone() = 0;
	virtual int hash();
	virtual std::string toString() const;

	virtual bool isInMorris(int8 pos) const;
	virtual bool isInMorris(int8 pos, int8 axis) const;
	virtual bool willBeInMorris(int8 src, int8 dest, pawn pawn) const;
	virtual ExpVector<int8> getAllPositions(pawn pawn) const;
	virtual ExpVector<int8> getAvailablePositions(int8 pos) const;

	//For debug
	void toStringToSend() const;

	virtual ~State();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const State &s);


#endif /* STATE_H_ */
