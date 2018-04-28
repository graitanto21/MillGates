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

