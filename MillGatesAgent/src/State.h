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

public:

	virtual bool setPawnAt(int8 x, int8 y, pawn value) = 0;
	// If coordinate is not valid, returns -1;
	virtual pawn getPawnAt(int8 x, int8 y) = 0;

	virtual void setPhase(int8 value) = 0;
	virtual int8 getPhase() const = 0;

	virtual void setWhiteCheckersOnBoard(std::string number) = 0;
	virtual int8 getWhiteCheckersOnBoard() = 0;

	virtual void setBlackCheckersOnBoard(std::string number) = 0;
	virtual int8 getBlackCheckersOnBoard() = 0;

	//Utiliy methods
	virtual State* clone() = 0;
	virtual int hash() = 0;
	virtual std::string toString() const = 0;
	virtual void toStringToSend() = 0;

	virtual ~State();
};

// For printing a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const State &s);

#endif /* STATE_H_ */
