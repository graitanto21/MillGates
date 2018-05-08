/*
 * Node.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "Node.h"

Node::Node(State * state, pawn pawn, unsigned int level) {

	this->_state = state;
	this->_player = pawn;
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

	addChild(new Node(getState()->result(action, getPlayer()),OPP(getPlayer()), getLevel() + 1));

}

ExpVector<Action> Node::expand() {

	return getState()->getActions(getPlayer());

}

ExpVector<Node*> Node::getChildren() {

	return _children;

}

pawn Node::getPlayer() {

	return this->_player;

}

Node::~Node() {
}

