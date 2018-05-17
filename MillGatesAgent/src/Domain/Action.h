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

class Action {
private:

	uint8 src;
	uint8 dest;
	uint8 removedPawn;
	std::string get2Dcoordinates(uint8 pos) const;

public:
	Action(uint8 src, uint8 dest, uint8 removedPawn);
	Action();

	virtual uint8 getSrc() const;
	virtual uint8 getDest() const;
	virtual uint8 getRemovedPawn() const;

	virtual std::string toString() const;

	virtual ~Action();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const Action &a);

#endif /* DOMAIN_ACTION_H_ */
