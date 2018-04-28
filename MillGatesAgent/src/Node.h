/*
 * Node.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef NODE_H_
#define NODE_H_

#include "State.h"

class Node {
private:

	State * state;

public:

	Node(State * state);

	virtual State * getState() const;

	virtual ~Node();

};

#endif /* NODE_H_ */
