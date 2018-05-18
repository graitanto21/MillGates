/*
 * Main.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#include <stdio.h>
#include <iostream>
#include <time.h>

#include "AI/IterativeDeepeningAI.h"
#include "Domain/CubeStateImpl.h"
#include "Domain/State.h"
#include "Netcode/connection.h"

#if !defined(DEBUG)

#define ACTION_STRLEN 7
#define STATE_STRLEN 82

using namespace std;

State * receiveState(State * old, pawn player) {
	char stateStr[STATE_STRLEN];
	State * state;
	uint8 myPawns;

	if (recv_data(stateStr, STATE_STRLEN) == FAILURE)
		exit(1);

	stateStr[STATE_STRLEN - 1] = '\0';

	state = new CubeStateImpl(stateStr);

	myPawns = old->getPawnsToPlay(player) + old->getPawnsOnBoard(player);

	state->setNewMorris(state->getPawnsToPlay(player) + state->getPawnsOnBoard(player) < myPawns);
	state->setPlayer(player);
	state->print();

	return state;
}

void sendAction(Action action) {
	char actionStr[ACTION_STRLEN];

	memset(actionStr, 0, sizeof(actionStr));
	strcpy(actionStr, action.toString().c_str());

	if (send_data(actionStr, ACTION_STRLEN) == FAILURE)
		exit(1);
}

void loop(pawn player) {

	AI * ai = new IterativeDeepeningAI();
	((IterativeDeepeningAI*)ai)->setAI(new NegaScoutAI());

	State * state = new CubeStateImpl();
	State * child;
	Action action;

	if (player == PAWN_WHITE) {

		state->setPlayer(PAWN_WHITE);
		while(1) {
			action = ai->choose(state);
			sendAction(action);
			child = state->result(action);
			ai->addHistory(child);
			delete state;
			state = receiveState(child, PAWN_WHITE);
			delete child;
		}
	}
	else if (player == PAWN_BLACK) {
		child = state->clone();
		state = receiveState(child, PAWN_WHITE);
		delete child;
		while(1) {
			action = ai->choose(state);
			sendAction(action);
			child = state->result(action);
			ai->addHistory(child);
			delete state;
			state = receiveState(child, PAWN_WHITE);
			delete child;
		}
	}

	delete ai;

}

int main(int argc, char* argv[]) {

	pawn player;

	if (argc != 2) {
		exit(1);
	}

	start_connection();

	srand(time(NULL));

	if (!strcmp(argv[1], "white"))
		player = PAWN_WHITE;
	else
		player = PAWN_BLACK;

	loop(player);

}
#endif
