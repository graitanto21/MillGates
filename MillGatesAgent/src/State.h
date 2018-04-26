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
	State(std::string stringFromServer);

	//Getters and setters
	virtual pawn getPawnAt(int x, int y, int z);
	virtual void setPawnAt(int x, int y, int z, pawn value);

	virtual bool setPawnAt(int8 x, int8 y, pawn value);
	// If coordinate is not valid, returns -1;
	virtual pawn getPawnAt(int8 x, int8 y);

	virtual void setPhase(int8 value);
	virtual int8 getPhase() const;

	virtual void setWhiteCheckersOnBoard(int8 number);
	virtual int8 getWhiteCheckersOnBoard();

	virtual void setBlackCheckersOnBoard(int8 number);
	virtual int8 getBlackCheckersOnBoard();

	//Utiliy methods
	virtual State* clone();
	virtual int hash();
	virtual std::string toString() const;
	virtual ~State();

	//Testing
	void toStringToSend();
};

// For printing a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const State &s);


#endif /* STATE_H_ */
