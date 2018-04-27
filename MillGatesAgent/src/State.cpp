/*
 * State.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Lorenzo Rosa (lorenzo.rosa.bo@gmail.com)
 */

#include "State.h"
#include "string.h"
#include "stdio.h"

State::~State() {}

std::ostream& operator<<(std::ostream &strm, const State &s){
	/* Here, I don't define the string representation directly,
	 * but I call the virtual method "toString". In this way, I
	 * emulate the Java behaviour of calling the "most specific"
	 * version of "toString" when printing an object (i.e., if the
	 * current instance is an instance of a subclass of State,
	 * I'll call the toString of that subclass).
	 */
	return strm << s.toString();
}

