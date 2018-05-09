/*
 * AI.h
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#ifndef AI_H_
#define AI_H_

#include "Action.h"
#include "State.h"

class AI {
public:

	virtual ~AI();
	virtual Action choose(State * state) = 0;

};

#endif /* AI_H_ */
