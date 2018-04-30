/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Node.h"

Node::Node(State * state, pawn pawn) {

	this->_state = state;
	this->_pawn = pawn;

}

State * Node::getState() const {

	return _state;

}

pawn Node::getPawn() {

	return this->_pawn;

}

Node::~Node() {
}

