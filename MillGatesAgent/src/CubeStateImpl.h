/*
 * CubeStateImpl.h
 *
 *  Created on: 28 apr 2018
 *      Author: Lorenzo Rosa
 */

#ifndef CUBESTATEIMPL_H_
#define CUBESTATEIMPL_H_

#include "Commons.h"
#include "State.h"

class CubeStateImpl : public State {

private:
	//Data structures
	pawn pawns[CUBE_SIZE_X][CUBE_SIZE_Y][CUBE_SIZE_Z];
	uint8 phase;

public:
	//Constructors
	CubeStateImpl();
	CubeStateImpl(std::string stringFromServer);

	//Getters and setters
	virtual pawn getPawnAt(uint8 x, uint8 y, uint8 z) const;
	virtual void setPawnAt(uint8 x, uint8 y, uint8 z, pawn value);

	void setPhase(uint8 currentPhase);
	uint8 getPhase() const;

	virtual State * clone() const;

	virtual ~CubeStateImpl();
};

#endif /* CUBESTATEIMPL_H_ */
