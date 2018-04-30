/*
 * Action.h
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#ifndef ACTION_H_
#define ACTION_H_

#include <iostream>
#include "commons.h"

class Action {
private:

	int8 src;
	int8 dest;
	int8 removedPawn;
	std::string get2Dcoordinates(int8 pos) const;

public:
	Action(int8 src, int8 dest, int8 removedPawn);
	Action();

	virtual int8 getSrc() const;
	virtual int8 getDest() const;
	virtual int8 getRemovedPawn() const;

	virtual std::string toString() const;

	virtual ~Action();
};

// To print a state without explicitly calling every time the ToString().
std::ostream& operator<<(std::ostream &strm, const Action &a);

#endif /* ACTION_H_ */
