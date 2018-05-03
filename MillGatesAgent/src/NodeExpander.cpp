/*
 * NodeExpander.cpp
 *
 *  Created on: Apr 28, 2018
 *      Author: Luca
 */

#include "NodeExpander.h"

NodeExpander::NodeExpander() {
	// TODO Auto-generated constructor stub

}

Node NodeExpander::performAction(Node node, Action action) {

	State * state = node.getState()->clone();

	int8 src = action.getSrc();
	int8 dest = action.getDest();
	int8 toRemove = action.getRemovedPawn();

	// fase 1 (pedina in dest)
	if(!IS_VALID(src) && IS_VALID(dest)) {
		state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), node.getPawn());
		if (node.getLevel() >= BLACK_PAWNS_COUNT)
			state->setPhase(PHASE_2);
	}
	// fasi 2 e 3 (pedina da src a dest)
	if(IS_VALID(src) && IS_VALID(dest)) {
		state->setPawnAt(GETX(src), GETY(src), GETZ(src), PAWN_NONE);
		state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), node.getPawn());
	}

	// rimozione pedina avversaria
	if(IS_VALID(toRemove)) {
		state->setPawnAt(GETX(toRemove), GETY(toRemove), GETZ(toRemove), PAWN_NONE);
		if (state->getWhiteCheckersOnBoard() == PAWNS_TO_ENTER_3RD_PHASE || state->getBlackCheckersOnBoard() == PAWNS_TO_ENTER_3RD_PHASE)
			state->setPhase(PHASE_3);
	}

	return Node(state, node.getPawn());

}

std::vector<Action> NodeExpander::addActionsForPawn(Node node, int8 src, std::vector<Action> actionBuffer) {

	State * state = node.getState();

	std::vector<int8> available = state->getAvailablePositions(src);
	for (int8 i = 0; i < available.size(); i++) {
		if (state->willBeInMorris(src, available[i], node.getPawn())) {
			std::vector<int8> pos = state->getAllPositions(OPP(node.getPawn()));
			bool added = false;
			for (int8 j = 0; j < pos.size(); j++)
				if (!state->isInMorris(pos[j])) {
					added = true;
					actionBuffer.push_back(Action(src, available[i], pos[j]));
				}
			if (!added)
				for (int8 j = 0; j < pos.size(); j++)
					actionBuffer.push_back(Action(src, available[i], pos[j]));
		}
		else
			actionBuffer.push_back(Action(src, available[i], POS_NULL));
	}

	return actionBuffer;

}

std::vector<Action> NodeExpander::expand(Node node) {

	State * state = node.getState();
	std::vector<Action> result(ACTION_VECTOR_DEFAULT_SIZE);

	if (state->getPhase() == PHASE_1) {

		result = addActionsForPawn(node, POS_NULL, result);

	}
	else {

		std::vector<int8> myPawns = state->getAllPositions(node.getPawn());
		for (int8 k = 0; k < myPawns.size(); k++)
			result = addActionsForPawn(node, myPawns[k], result);

	}

	return result;

}

NodeExpander::~NodeExpander() {
}
