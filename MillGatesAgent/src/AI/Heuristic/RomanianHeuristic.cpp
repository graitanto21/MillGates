/*
 * RomanianHeuristic.cpp
 *
 *  Created on: May 16, 2018
 *      Author: Luca
 */

#include "RomanianHeuristic.h"

RomanianHeuristic::RomanianHeuristic() {}

eval_t RomanianHeuristic::evaluate(State * state, bool terminal, bool loop) {

	eval_t result = 0;

	uint8 whiteToPlay = state->getPawnsToPlay(PAWN_WHITE);
	uint8 blackToPlay = state->getPawnsToPlay(PAWN_BLACK);
	uint8 whiteOnBoard = state->getPawnsOnBoard(PAWN_WHITE);
	uint8 blackOnBoard = state->getPawnsOnBoard(PAWN_BLACK);

	if (loop)
		return result;

	/* Closed Morris refers to a new closed morris, that offers the advantage to
	 * grab one opponent piece.
	 *
	 *  1  if a morris is closed by the WHITE player
	 *
	 * -1  if a morris is closed by the BLACK player
	 *
	 *  0 otherwise
	 */
	sint8 morrisLastTurn; // (1)
	if (state->getPlayer() == PAWN_BLACK && state->getNewMorris())
		morrisLastTurn = 1;
	else if (state->getPlayer() == PAWN_WHITE && state->getNewMorris())
		morrisLastTurn = -1;
	else
		morrisLastTurn = 0;

	if (blackToPlay > 0) { //Phase 1

		sint8 morrises; // (2)
		morrises = state->morrisCount(PAWN_WHITE) - state->morrisCount(PAWN_BLACK);

		sint8 blockedPawns; // (3)
		blockedPawns = state->blockedPawnCount(PAWN_BLACK) - state->blockedPawnCount(PAWN_WHITE);

		sint8 pawns; // (4)
		pawns = whiteToPlay + whiteOnBoard - blackToPlay - blackOnBoard;

		sint8 potentialSingleMorrises; // (5)
		potentialSingleMorrises = state->potentialMorrisCount(PAWN_WHITE) - state->potentialMorrisCount(PAWN_BLACK);

		sint8 potentialDoubleMorrises; // (6)
		potentialDoubleMorrises = state->potentialDoubleMorrisCount(PAWN_WHITE) - state->potentialDoubleMorrisCount(PAWN_BLACK);

		result = 18 * morrisLastTurn +
				26 	* morrises +
				1 	* blockedPawns +
				9 	* pawns +
				10	* potentialSingleMorrises +
				7 	* potentialDoubleMorrises;
	}
	else if ((state->getPlayer() == PAWN_BLACK && whiteOnBoard > 3) || (state->getPlayer() == PAWN_WHITE && blackOnBoard > 3)) { //Phase 2

		sint8 morrises; // (2)
		morrises = state->morrisCount(PAWN_BLACK) - state->morrisCount(PAWN_WHITE);

		sint8 blockedPawns; // (3)
		blockedPawns = state->blockedPawnCount(PAWN_BLACK) - state->blockedPawnCount(PAWN_WHITE);

		sint8 pawns; // (4)
		pawns = whiteToPlay + whiteOnBoard - blackToPlay - blackOnBoard;

		sint8 doubleMorrises;
		doubleMorrises = state->doubleMorrisCount(PAWN_WHITE) - state->doubleMorrisCount(PAWN_BLACK);

		sint8 winning;
		winning = (terminal) ? (state->getPlayer() == PAWN_WHITE ? -1 : 1) : 0;

		result = 14 	* morrisLastTurn +
				43 		* morrises +
				10 		* blockedPawns +
				11 		* pawns +
				8 		* doubleMorrises +
				1086 	* winning;
	}
	else if ((state->getPlayer() == PAWN_BLACK && whiteOnBoard <= 3) || (state->getPlayer() == PAWN_WHITE && blackOnBoard <= 3)) { //Phase 3

		sint8 potentialSingleMorrises; // (5)
		potentialSingleMorrises = state->potentialMorrisCount(PAWN_WHITE) - state->potentialMorrisCount(PAWN_BLACK);

		sint8 potentialDoubleMorrises; // (6)
		potentialDoubleMorrises = state->potentialDoubleMorrisCount(PAWN_WHITE) - state->potentialDoubleMorrisCount(PAWN_BLACK);

		sint8 winning;
		winning = (terminal) ? (state->getPlayer() == PAWN_WHITE ? -1 : 1) : 0;

		result = 16 	* morrisLastTurn +
				10 		* potentialSingleMorrises +
				1 		* potentialDoubleMorrises +
				1190 	* winning;
	}

	return result;
}

RomanianHeuristic::~RomanianHeuristic() {}

