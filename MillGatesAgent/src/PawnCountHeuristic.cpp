/*
 * PawnCountHeuristic.cpp
 *
 *  Created on: May 16, 2018
 *      Author: Luca
 */

#include "PawnCountHeuristic.h"

PawnCountHeuristic::PawnCountHeuristic() {}

eval_t PawnCountHeuristic::evaluate(State * state, bool terminal, bool loop) {

		if (terminal)
			return state->utility();

		if (loop)
			return 0;

		sint8 white = state->getPawnsOnBoard(PAWN_WHITE) + state->getPawnsToPlay(PAWN_WHITE);
		sint8 black = state->getPawnsOnBoard(PAWN_BLACK) + state->getPawnsToPlay(PAWN_BLACK);

		return white - black;
}

PawnCountHeuristic::~PawnCountHeuristic() {}

