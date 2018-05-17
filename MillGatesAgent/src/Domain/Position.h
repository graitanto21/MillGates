/*
 * Position.h
 *
 *  Created on: May 17, 2018
 *      Author: Luca
 */

#ifndef DOMAIN_POSITION_H_
#define DOMAIN_POSITION_H_

#include "../Commons.h"

typedef struct Position{
	sint8 x;
	sint8 y;
	sint8 z;

	bool operator==(const Position& rhs)
	{
	    return x == rhs.x && y == rhs.y && z == rhs.z;
	}

} Position;

const Position POS_NULL = {-1,0,0};

#endif /* DOMAIN_POSITION_H_ */
