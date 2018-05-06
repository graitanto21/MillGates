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
#include "Action.h"
#include <iostream>
#include <string>

class State {

private:

	virtual ExpVector<Action> addActionsForPawn(int8 src, ExpVector<Action> actionBuffer, pawn player) const;

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

	virtual void setWhitePawnsToPlayStr(std::string number);
	virtual int8 getWhitePawnsToPlayStr() const;

	virtual void setBlackPawnsToPlayStr(std::string number);
	virtual int8 getBlackPawnsToPlayStr() const;

	virtual void setPawnsOnBoard(pawn pawn, int8 count);
	virtual int8 getPawnsOnBoard(pawn pawn) const;

	virtual pawn getPawnsToPlay(pawn player) const;
	virtual void setPawnsToPlay(pawn player, int8 count);

	//Utility methods
	virtual State* clone() const = 0;
	virtual int hash();
	virtual std::string toString() const;

	virtual bool isInMorris(int8 pos) const;
	virtual bool isInMorris(int8 pos, int8 axis) const;
	virtual bool willBeInMorris(int8 src, int8 dest, pawn pawn) const;
	virtual ExpVector<int8> getAllPositions(pawn pawn) const;
	virtual ExpVector<int8> getAvailablePositions(int8 pos) const;

	virtual ExpVector<Action> getActions(pawn player) const;
	virtual State * result(Action action, pawn player) const;


	//For debug
	void toStringToSend() const;

	virtual ~State();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const State &s);


#endif /* STATE_H_ */
