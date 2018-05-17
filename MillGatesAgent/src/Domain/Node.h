/*
 * Node.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef DOMAIN_NODE_H_
#define DOMAIN_NODE_H_

#include "../Utils/ExpVector.h"
#include "State.h"

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
	virtual ExpVector<Action> * expand();

	virtual void addChild(Node * node);
	virtual ExpVector<Node*> getChildren();

	virtual ~Node();

};

#endif /* DOMAIN_NODE_H_ */
