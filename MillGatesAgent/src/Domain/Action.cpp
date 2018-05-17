/*
 * Action.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Action.h"

Action::Action(Position src, Position dest, Position removedPawn) {

	this->src = src;
	this->dest = dest;
	this->removedPawn = removedPawn;

}

Action::Action() {

	this->src = POS_NULL;
	this->dest = POS_NULL;
	this->removedPawn = POS_NULL;

}

Position Action::getSrc() const {
	return src;
}

Position Action::getDest() const {
	return dest;
}

Position Action::getRemovedPawn() const {
	return removedPawn;
}

std::string Action::get2Dcoordinates(Position pos) const {
	if(!IS_VALID(pos))
		return "";
	std::string res("");
	uint8 i = pos.x;
	uint8 j = pos.y;
	uint8 k = pos.z;

	if(j==0) { //a,b,c
			if (k==2) {
				res.append("a");
				res.append(std::string(1, '0' + 7-(3*i)));
			}
			else if (k==1) {
				res.append("b");
				res.append(std::string(1, '0' + 6-(2*i) ));
			}
			else if (k==0) {
				res.append("c");
				res.append(std::string(1, '0' + 5-i ));
			}
	}
	else if (j==1) { //d
			res.append("d");
			if (i==2) //1,2,3
				res.append(std::string(1, '0' + 3-k ));
			else if (i==0)
				res.append(std::string(1, '0' + 5+k ));
			else
				res.append("4"); //d4, central pos
	}
	else if (j==2){  //e,f,g
			if (k==2) {
				res.append("g");
				res.append(std::string(1, '0' + 7-(3*i) ));
			}
			else if (k==1) {
				res.append("f");
				res.append(std::string(1, '0' + 6-(2*i) ));
			}
			else if (k==0) {
				res.append("e");
				res.append(std::string(1, '0' + 5-i ));
			}
	}

	return res;
}

std::string Action::toString() const {
	return get2Dcoordinates(src).append(get2Dcoordinates(dest).append(get2Dcoordinates(removedPawn)));
}

Action::~Action() {
}

std::ostream& operator<<(std::ostream &strm, const Action &a){
	return strm << a.toString();
}
