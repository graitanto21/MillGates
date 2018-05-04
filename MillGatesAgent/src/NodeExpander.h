/*
 * NodeExpander.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef NODEEXPANDER_H_
#define NODEEXPANDER_H_

#include "Node.h"
#include "Action.h"
#include "ExpVector.h"
#include <iostream>

class NodeExpander {

private:

	virtual ExpVector<Action> addActionsForPawn(Node node, int8 src, ExpVector<Action> actionBuffer);

public:

	NodeExpander();

	virtual void performAction(Node * node, Action action);
	virtual ExpVector<Action> expand(Node node);

	virtual ~NodeExpander();

};

#endif /* NODEEXPANDER_H_ */
