/*
 * Action.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Action.h"

Action::Action(int8 src, int8 dest, int8 removedPawn) {

	this->src = src;
	this->dest = dest;
	this->removedPawn = removedPawn;

}

Action::Action() {

	this->src = POS_NULL;
	this->dest = POS_NULL;
	this->removedPawn = POS_NULL;

}

int8 Action::getSrc() const {
	return src;
}

int8 Action::getDest() const {
	return dest;
}

int8 Action::getRemovedPawn() const {
	return removedPawn;
}

std::string Action::toString() const {

	return "";
}

Action::~Action() {
}

std::ostream& operator<<(std::ostream &strm, const Action &a){
	return strm << a.toString();
}
