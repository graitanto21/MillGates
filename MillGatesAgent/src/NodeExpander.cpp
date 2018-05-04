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

void NodeExpander::performAction(Node * node, Action action) {

	State * state = node->getState()->clone();

	int8 src = action.getSrc();
	int8 dest = action.getDest();
	int8 toRemove = action.getRemovedPawn();

	// fase 1 (pedina in dest)
	if(!IS_VALID(src) && IS_VALID(dest)) {
		state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), node->getPawn());
		state->setPawnsOnBoard(node->getPawn(), state->getPawnsOnBoard(node->getPawn()) + 1);
		if (node->getLevel() >= BLACK_PAWNS_COUNT + WHITE_PAWNS_COUNT)
			state->setPhase(PHASE_2);
	}
	// fasi 2 e 3 (pedina da src a dest)
	if(IS_VALID(src) && IS_VALID(dest)) {
		state->setPawnAt(GETX(src), GETY(src), GETZ(src), PAWN_NONE);
		state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), node->getPawn());
	}

	// rimozione pedina avversaria
	if(IS_VALID(toRemove)) {
		state->setPawnAt(GETX(toRemove), GETY(toRemove), GETZ(toRemove), PAWN_NONE);
		state->setPawnsOnBoard(OPP(node->getPawn()), state->getPawnsOnBoard(OPP(node->getPawn())) - 1);
		if (state->getWhitePawnsOnBoardStr() == PAWNS_TO_ENTER_3RD_PHASE || state->getBlackPawnsOnBoardStr() == PAWNS_TO_ENTER_3RD_PHASE)
			state->setPhase(PHASE_3);
	}

	node->addChild(new Node(state,OPP(node->getPawn()), node->getLevel() + 1));

}

ExpVector<Action> NodeExpander::addActionsForPawn(Node node, int8 src, ExpVector<Action> actionBuffer) {

	State * state = node.getState();

	ExpVector<int8> available = state->getAvailablePositions(src);
	for (int8 i = 0; i < available.getLogicSize(); i++) {
		if (state->willBeInMorris(src, available.get(i), node.getPawn())) {
			ExpVector<int8> pos = state->getAllPositions(OPP(node.getPawn()));
			bool added = false;
			for (int8 j = 0; j < pos.getLogicSize(); j++)
				if (!state->isInMorris(pos.get(j))) {
					added = true;
					actionBuffer.add(Action(src, available.get(i), pos.get(j)));
				}
			if (!added)
				for (int8 j = 0; j < pos.getLogicSize(); j++)
					actionBuffer.add(Action(src, available.get(i), pos.get(j)));
		}
		else
			actionBuffer.add(Action(src, available.get(i), POS_NULL));
	}

	return actionBuffer;

}

ExpVector<Action> NodeExpander::expand(Node node) {

	State * state = node.getState();
	ExpVector<Action> result(ACTION_VECTOR_DEFAULT_SIZE);

	if (state->getPhase() == PHASE_1) {

		result = addActionsForPawn(node, POS_NULL, result);

	}
	else {

		ExpVector<int8> myPawns = state->getAllPositions(node.getPawn());
		for (int8 k = 0; k < myPawns.getLogicSize(); k++)
			result = addActionsForPawn(node, myPawns.get(k), result);

	}

	return result;

}

NodeExpander::~NodeExpander() {
}
