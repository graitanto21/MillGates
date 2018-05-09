/*
 * Node.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef NODE_H_
#define NODE_H_

#include "State.h"
#include "ExpVector.h"

//typedef unsigned char sasso;

class Node {
private:

	State * _state;
	unsigned int _level;
	ExpVector<Node*> _children;

public:

	Node(State * _state, unsigned int level);

	virtual State * getState() const;

	virtual unsigned int getLevel() const;
	virtual void performAction(Action action);
	virtual ExpVector<Action> expand();

	virtual void addChild(Node * node);
	virtual ExpVector<Node*> getChildren();

	virtual ~Node();

};

#endif /* NODE_H_ */
