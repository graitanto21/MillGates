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

	return node(state);

}

std::vector<Action> NodeExpander::expand(Node node) {

	State * state = node.getState();
	std::vector<Action> result(ACTION_VECTOR_DEFAULT_SIZE);

	switch (state->getPhase()) {

	case (PHASE_1) :

				for (int8 x = 0; x < CUBE_SIZE_X; x++)
					for (int8 y = 0; y < CUBE_SIZE_Y; y++)
						for (int8 z = 0; z < CUBE_SIZE_Z; z++)
							if (state->getPawnAt(x, y, z) == PAWN_NONE) {

								if (state->willBeInMorris(NEW_POS(x,y,z), pawn)) {
									// Add all possibilities
								}
								else
									result.push_back(Action(POS_NULL, NEW_POS(x,y,z), POS_NULL));

							}


	break;

	case (PHASE_2) :

			break;

	case (PHASE_3) :

			break;

	}

	return result;

}

NodeExpander::~NodeExpander() {
	// TODO Auto-generated destructor stub
}

