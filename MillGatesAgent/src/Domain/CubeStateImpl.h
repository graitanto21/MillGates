/*
 * CubeStateImpl.h
 *
 *  Created on: 28 apr 2018
 *      Author: Lorenzo Rosa
 */

#ifndef DOMAIN_CUBESTATEIMPL_H_
#define DOMAIN_CUBESTATEIMPL_H_

#include "../Commons.h"
#include "State.h"

class CubeStateImpl : public State {

private:
	//Data structures
	pawn _pawns[CUBE_SIZE_X][CUBE_SIZE_Y][CUBE_SIZE_Z];
	pawn _player;

public:
	//Constructors
	CubeStateImpl();
	CubeStateImpl(std::string stringFromServer);

	//Getters and setters
	virtual pawn getPawnAt(uint8 x, uint8 y, uint8 z) const;
	virtual void setPawnAt(uint8 x, uint8 y, uint8 z, pawn value);

	virtual pawn getPlayer() const;
	virtual void setPlayer(pawn player);

	virtual State * clone() const;

	virtual ~CubeStateImpl();
};

#endif /* DOMAIN_CUBESTATEIMPL_H_ */
