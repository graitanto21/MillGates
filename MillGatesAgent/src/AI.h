/*
 * AI.h
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#ifndef AI_H_
#define AI_H_

#include "Action.h"
#include "Node.h"

class AI {
public:

	virtual ~AI();
	virtual Action choose(Node node) = 0;

};

#endif /* AI_H_ */
