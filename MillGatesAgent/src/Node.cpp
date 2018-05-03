/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Node.h"

Node::Node(State * state, pawn pawn, unsigned int level) {

	this->_state = state;
	this->_pawn = pawn;
	this->_level = level;

}

State * Node::getState() const {

	return _state;

}

unsigned int Node::getLevel() const {

	return _level;

}

pawn Node::getPawn() {

	return this->_pawn;

}

Node::~Node() {
}

