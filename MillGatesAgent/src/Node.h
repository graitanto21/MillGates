/*
 * Node.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef NODE_H_
#define NODE_H_

#include "State.h"

//typedef unsigned char sasso;

class Node {
private:

	State * _state;
	pawn _pawn;
	unsigned int _level;

public:

	Node(State * _state, pawn pawn, unsigned int level);

	virtual State * getState() const;

	virtual unsigned int getLevel() const;

	virtual pawn getPawn();

	virtual ~Node();

};

#endif /* NODE_H_ */
