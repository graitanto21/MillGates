/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Node.h"

Node::Node(State * state, unsigned char pawn) {

	this->state = state;
	this->pawn = pawn;

}

State * Node::getState() const {

	return state;

}

unsigned char Node::getPawn() {

	return this->pawn;

}

Node::~Node() {
}

