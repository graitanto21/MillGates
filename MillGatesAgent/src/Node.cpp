/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Node.h"

Node::Node(State * state) {

	this->state = state;

}

State * Node::getState() const {

	return state;

}

Node::~Node() {
}

