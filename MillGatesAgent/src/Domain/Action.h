/*
 * Action.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef DOMAIN_ACTION_H_
#define DOMAIN_ACTION_H_

#include <iostream>
#include "../Commons.h"
#include "Position.h"

class Action {
private:

	Position src;
	Position dest;
	Position removedPawn;
	std::string get2Dcoordinates(Position pos) const;

public:
	Action(Position src, Position dest, Position removedPawn);
	Action();

	virtual Position getSrc() const;
	virtual Position getDest() const;
	virtual Position getRemovedPawn() const;

	virtual std::string toString() const;

	virtual ~Action();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const Action &a);

#endif /* DOMAIN_ACTION_H_ */
