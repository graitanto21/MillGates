/*
 * CubeState.h
 *
 *  Created on: 26 apr 2018
 *      Author: Lorenzo Rosa
 */

#ifndef DOMAIN_STATE_H_
#define DOMAIN_STATE_H_

#include "../Commons.h"
#include <iostream>
#include <string>

#include "../Utils/ExpVector.h"
#include "Action.h"

class State {

private:

	virtual ExpVector<Action> addActionsForPawn(Position src, ExpVector<Action> actionBuffer) const;

public:

	//Getters and setters

	//2D (concrete mapping calling abstract 3D getters/setters).
	virtual bool setPawnAt2D(uint8 x, uint8 y, pawn value);
	// If coordinate is not valid, returns -1;
	virtual pawn getPawnAt2D(uint8 x, uint8 y) const;

	//3D (abstract)
	virtual pawn getPawnAt(sint8 x, sint8 y, sint8 z) const = 0;
	virtual void setPawnAt(sint8 x, sint8 y, sint8 z, pawn value) = 0;

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

	virtual void setPawnsToPlay(pawn player, uint8 count);
	virtual uint8 getPawnsToPlay(pawn player) const;

	virtual pawn getPlayer() const = 0;
	virtual void setPlayer(pawn player) = 0;

	virtual void setMorrisLastTurn(pawn player, bool value);
	virtual bool getMorrisLastTurn(pawn player) const;

	virtual uint8 morrisCount(pawn player) const;
	virtual uint8 blockedPawnCount(pawn player) const;
	virtual uint8 potentialMorrisCount(pawn player) const;
	virtual uint8 potentialDoubleMorrisCount(pawn player) const;
	virtual uint8 doubleMorrisCount(pawn player) const;

	//Utility methods
	virtual State* clone() const = 0;
	virtual std::string toString() const;
	virtual std::string toNiceString() const;

	virtual bool isInMorris(Position pos) const;
	virtual bool isInMorrisAxis(Position pos, uint8 axis) const;
	virtual bool willBeInMorris(Position src, Position dest, pawn pawn) const;
	virtual bool willBeInMorrisAxis(Position src, Position dest, pawn pawn, uint8 axis) const;
	virtual ExpVector<Position> getAllPositions(pawn pawn) const;
	virtual ExpVector<Position> getAvailablePositions(Position pos) const;

	virtual ExpVector<Action> * getActions() const;
	virtual State * result(Action action) const;

	virtual bool isTerminal() const;
	virtual eval_t utility() const;


	//For debug
	void toStringToSend() const;

	virtual ~State();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const State &s);


#endif /* DOMAIN_STATE_H_ */
