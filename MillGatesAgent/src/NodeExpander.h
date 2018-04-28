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
#include "Commons.h"
#include <iostream>
#include <vector>

class NodeExpander {
public:

	NodeExpander();

	virtual Node performAction(Node node, Action action);
	virtual std::vector<Action> expand(Node node);

	virtual ~NodeExpander();

};

#endif /* NODEEXPANDER_H_ */
