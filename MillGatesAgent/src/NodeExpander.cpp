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

	State * state = node.getState();

	int8 src = action.getSrc();
	int8 dest = action.getDest();
	int8 toRemove = action.getRemovedPawn();

	pawn ourPawn = node.getPawn();
	pawn opponentPawn = (ourPawn == PAWN_WHITE) ? PAWN_BLACK : PAWN_WHITE;

	// fase 1 (pedina in dest)
	if(!IS_VALID(src) && IS_VALID(dest)) {
		if(state->getPawnAt(GETX(dest), GETY(dest), GETZ(dest)) == PAWN_NONE) // controllo necessario?
			state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), ourPawn);
	}

	// fasi 2 e 3 (pedina da src a dest)
	if(IS_VALID(src) && IS_VALID(dest)) {
		// se conosciamo il nostro colore è necessario ottenere srcPawn?
		pawn srcPawn = state->getPawnAt(GETX(src), GETY(src), GETZ(src));
		pawn destPawn = state->getPawnAt(GETX(dest), GETY(dest), GETZ(dest));
		if(srcPawn == ourPawn && destPawn == PAWN_NONE) { // controlli necessari?
			state->setPawnAt(GETX(src), GETY(src), GETZ(src), PAWN_NONE);
			state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), srcPawn);
		}
	}

	// rimozione pedina avversaria
	if(IS_VALID(toRemove)) {
		pawn pawnToRemove = state->getPawnAt(GETX(toRemove), GETY(toRemove), GETZ(toRemove));
		if (pawnToRemove == opponentPawn) // controllo necessario?
			state->setPawnAt(GETX(toRemove), GETY(toRemove), GETZ(toRemove), PAWN_NONE);
	}

	return Node(state, ourPawn);

}

std::vector<Action> NodeExpander::addActionsForPawn(Node node, int8 src, std::vector<Action> actionBuffer) {

	State * state = node.getState();

	std::vector<int8> available = state->getAvailablePositions(src);
	for (int8 i = 0; i < available.size(); i++) {
		if (state->willBeInMorris(available[i], node.getPawn())) {
			std::vector<int8> pos = state->getAllPositions(OPP(node.getPawn()));
			bool added = false;
			for (int8 j = 0; j < pos.size(); j++)
				if (!state->isInMorris(pos[j])) {
					added = true;
					actionBuffer.push_back(Action(POS_NULL, available[i], pos[j]));
				}
			if (!added)
				for (int8 j = 0; j < pos.size(); j++)
					actionBuffer.push_back(Action(POS_NULL, available[i], pos[j]));
		}
		else
			actionBuffer.push_back(Action(POS_NULL, available[i], POS_NULL));
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

#include "CubeStateImpl.h"

int main(void) {

	State * state = new CubeStateImpl();

	state->setPhase(PHASE_2);
	state->setBlackCheckersOnBoard("9");
	state->setWhiteCheckersOnBoard("8");

	state->setPawnAt2D('a', '1', PAWN_WHITE);
	state->setPawnAt2D('a', '4', PAWN_WHITE);
	state->setPawnAt2D('a', '7', PAWN_BLACK);

	state->setPawnAt2D('b', '2', PAWN_BLACK);
	state->setPawnAt2D('b', '4', PAWN_BLACK);
	state->setPawnAt2D('b', '6', PAWN_BLACK);

	state->setPawnAt2D('c', '3', PAWN_BLACK);
	state->setPawnAt2D('c', '4', PAWN_WHITE);
	state->setPawnAt2D('c', '5', PAWN_BLACK);

	state->setPawnAt2D('d', '1', PAWN_BLACK);
	state->setPawnAt2D('d', '3', PAWN_WHITE);
	state->setPawnAt2D('d', '5', PAWN_BLACK);
	state->setPawnAt2D('d', '7', PAWN_BLACK);

	state->setPawnAt2D('e', '4', PAWN_WHITE);
	state->setPawnAt2D('e', '5', PAWN_WHITE);

	state->setPawnAt2D('f', '4', PAWN_WHITE);

	state->setPawnAt2D('g', '7', PAWN_WHITE);

	Node node(state, PAWN_WHITE);

	NodeExpander expander;

	//	std::vector<int8> res = state->getAllPositions(PAWN_NONE);
	//	std::cout << "Azioni possibili: " << res.size() << "\n";
	//	for (int8 i = 0; i < res.size(); i++)
	//		std::cout << (int)i << "  " << (int)GETX(res[i]) << " " << (int)GETY(res[i]) << " "<< (int)GETZ(res[i]) << "\n";

	std::vector<Action> res = expander.expand(node);

	std::cout << "Azioni possibili: " << res.size() << "\n";
	int x, y, z;
	for (int8 i = 0; i < res.size(); i++) {
		x = GETX(res[i].getDest());
		y = GETY(res[i].getDest());
		z = GETZ(res[i].getDest());
		std::cout << (int)i << " " << res[i] << " => " << x << " " << y << " "<< z << "\n";
	}
}

