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

	virtual ExpVector<Action> addActionsForPawn(uint8 src, ExpVector<Action> actionBuffer, pawn player) const;

public:

	//Getters and setters

	//2D (concrete mapping calling abstract 3D getters/setters).
	virtual bool setPawnAt2D(uint8 x, uint8 y, pawn value);
	// If coordinate is not valid, returns -1;
	virtual pawn getPawnAt2D(uint8 x, uint8 y) const;

	//3D (abstract)
	virtual pawn getPawnAt(uint8 x, uint8 y, uint8 z) const = 0;
	virtual void setPawnAt(uint8 x, uint8 y, uint8 z, pawn value) = 0;

	virtual void setPhase(uint8 value) = 0;
	virtual uint8 getPhase() const = 0;

	virtual void setWhitePawnsOnBoardStr(std::string number);
	virtual uint8 getWhitePawnsOnBoardStr() const;

	virtual void setBlackPawnsOnBoardStr(std::string number);
	virtual uint8 getBlackPawnsOnBoardStr() const;

	virtual void setWhitePawnsToPlayStr(std::string number);
	virtual uint8 getWhitePawnsToPlayStr() const;

	virtual void setBlackPawnsToPlayStr(std::string number);
	virtual uint8 getBlackPawnsToPlayStr() const;

	virtual void setPawnsOnBoard(pawn pawn, uint8 count);
	virtual uint8 getPawnsOnBoard(pawn pawn) const;

	virtual pawn getPawnsToPlay(pawn player) const;
	virtual void setPawnsToPlay(pawn player, uint8 count);

	//Utility methods
	virtual State* clone() const = 0;
	virtual int hash();
	virtual std::string toString() const;

	virtual bool isInMorris(uint8 pos) const;
	virtual bool isInMorris(uint8 pos, uint8 axis) const;
	virtual bool willBeInMorris(uint8 src, uint8 dest, pawn pawn) const;
	virtual ExpVector<uint8> getAllPositions(pawn pawn) const;
	virtual ExpVector<uint8> getAvailablePositions(uint8 pos) const;

	virtual ExpVector<Action> getActions(pawn player) const;
	virtual State * result(Action action, pawn player) const;

	virtual bool isTerminal(pawn player) const;
	virtual sint8 utility(pawn player) const;


	//For debug
	void toStringToSend() const;

	virtual ~State();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const State &s);


#endif /* STATE_H_ */
