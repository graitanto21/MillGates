/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Node.h"

Node::Node(State * state, unsigned int level) {

	this->_state = state;
	this->_level = level;

}

State * Node::getState() const {

	return _state;

}

unsigned int Node::getLevel() const {

	return _level;

}

void Node::addChild(Node * node) {

	this->_children.add(node);

}

void Node::performAction(Action action) {

	addChild(new Node(getState()->result(action), getLevel() + 1));

}

ExpVector<Action> Node::expand() {

	return getState()->getActions();

}

ExpVector<Node*> Node::getChildren() {

	return _children;

}

Node::~Node() {
}

