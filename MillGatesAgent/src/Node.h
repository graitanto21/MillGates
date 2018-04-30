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

	State * state;
	pawn pawn;

public:

	Node(State * state, unsigned char pawn);

	virtual State * getState() const;

	virtual unsigned char getPawn();

	virtual ~Node();

};

#endif /* NODE_H_ */
