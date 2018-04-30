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
	int8 removedPawn = action.getRemovedPawn();

	// fase 1 (pedina in dest)
	if(!IS_VALID(src) && IS_VALID(dest)) {
		/* TODO bisogna tenere traccia del nostro colore: dove?
		 * if(state->getPawnAt(GETX(dest), GETY(dest), GETZ(dest)) == PAWN_NONE) // controllo necessario?
		 * 	   state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), PAWN_); // TODO inserire pedina del nostro colore
		 */
	}

	// fasi 2 e 3 (pedina da src a dest)
	if(IS_VALID(src) && IS_VALID(dest)) {
		// se conosciamo il nostro colore è necessario ottenere srcPawn?
		pawn srcPawn = state->getPawnAt(GETX(src), GETY(src), GETZ(src));
		pawn destPawn = state->getPawnAt(GETX(dest), GETY(dest), GETZ(dest));
		if(srcPawn != PAWN_NONE && destPawn == PAWN_NONE) { // controlli necessari? controllare che srcPawn sia del nostro colore?
			// volendo si può creare un metodo che dato uno stato, src e dest, sposti la pedina da src a dest
			state->setPawnAt(GETX(src), GETY(src), GETZ(src), PAWN_NONE);
			state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), srcPawn);
		}
	}

	// rimozione pedina avversaria
	if(IS_VALID(removedPawn)) {
		pawn removedPawn = state->getPawnAt(GETX(removedPawn), GETY(removedPawn), GETZ(removedPawn));
		if (removedPawn != PAWN_NONE) // controllo necessario? controllare che removedPawn sia del colore avversario?
			state->setPawnAt(GETX(removedPawn), GETY(removedPawn), GETZ(removedPawn), PAWN_NONE);
	}

	return Node(state, 2); //TODO: CAMBIAMI!!

}

std::vector<Action> NodeExpander::expand(Node node) {

	State * state = node.getState();
	std::vector<Action> result(ACTION_VECTOR_DEFAULT_SIZE);

	if (state->getPhase() == PHASE_1) {

		std::vector<int8> available = state->getAllPositions(PAWN_NONE);
		for (int8 i = 0; i < available.size(); i++) {
			if (state->willBeInMorris(available[i], node.getPawn())) {
				std::vector<int8> pos = state->getAllPositions(OPP(node.getPawn()));
				bool added = false;
				for (int8 j = 0; j < pos.size(); j++)
					if (!state->isInMorris(pos[j])) {
						added = true;
						result.push_back(Action(POS_NULL, available[i], pos[j]));
					}
				if (!added)
					for (int8 j = 0; j < pos.size(); j++)
						result.push_back(Action(POS_NULL, available[i], pos[j]));
			}
			else
				result.push_back(Action(POS_NULL, available[i], POS_NULL));
		}
	}
	else if (state->getPhase() == PHASE_2) {

		std::vector<int8> myPawns = state->getAllPositions(node.getPawn());
		for (int8 k = 0; k < myPawns.size(); k++) {
			std::vector<int8> available = state->getAvailablePositions(myPawns[k]);
			for (int8 i = 0; i < available.size(); i++) {
				if (state->willBeInMorris(available[i], node.getPawn())) {
					std::vector<int8> pos = state->getAllPositions(OPP(node.getPawn()));
					bool added = false;
					for (int8 j = 0; j < pos.size(); j++)
						if (!state->isInMorris(pos[j])) {
							added = true;
							result.push_back(Action(myPawns[k], available[i], pos[j]));
						}
					if (!added)
						for (int8 j = 0; j < pos.size(); j++)
							result.push_back(Action(myPawns[k], available[i], pos[j]));
				}
				else
					result.push_back(Action(myPawns[k], available[i], POS_NULL));
			}
		}

	}

	else if (state->getPhase() == PHASE_3) {

		std::vector<int8> myPawns = state->getAllPositions(node.getPawn());
		for (int8 k = 0; k < myPawns.size(); k++) {
			std::vector<int8> available = state->getAllPositions(PAWN_NONE);
			for (int8 i = 0; i < available.size(); i++) {
				if (state->willBeInMorris(available[i], node.getPawn())) {
					std::vector<int8> pos = state->getAllPositions(OPP(node.getPawn()));
					bool added = false;
					for (int8 j = 0; j < pos.size(); j++)
						if (!state->isInMorris(pos[j])) {
							added = true;
							result.push_back(Action(myPawns[k], available[i], pos[j]));
						}
					if (!added)
						for (int8 j = 0; j < pos.size(); j++)
							result.push_back(Action(myPawns[k], available[i], pos[j]));
				}
				else
					result.push_back(Action(myPawns[k], available[i], POS_NULL));
			}
		}
	}

	return result;

}

NodeExpander::~NodeExpander() {
}

#include "CubeStateImpl.h"

int main(void) {

	State * state = new CubeStateImpl();

	Node node(state, PAWN_WHITE);

	NodeExpander expander;

//	std::vector<int8> res = state->getAllPositions(PAWN_NONE);
//	std::cout << "Azioni possibili: " << res.size() << "\n";
//	for (int8 i = 0; i < res.size(); i++)
//		std::cout << (int)i << "  " << (int)GETX(res[i]) << " " << (int)GETY(res[i]) << " "<< (int)GETZ(res[i]) << "\n";

	std::vector<Action> res = expander.expand(node);

	std::cout << "Azioni possibili: " << res.size() << "\n";

	for (int8 i = 0; i < res.size(); i++)
		std::cout << (int)i << " " << res[i].toString() << "\n";

}

