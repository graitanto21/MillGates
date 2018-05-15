///*
// * Main.cpp
// *
// *  Created on: Apr 21, 2018
// *      Author: Luca
// */
//
//#include <stdio.h>
//#include "State.h"
//#include "CubeStateImpl.h"
//#include "IterativeDeepeningAI.h"
//#include "connection.h"
//#include <iostream>
//#include <time.h>
//
//#define ACTION_STRLEN 7
//#define STATE_STRLEN 82
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	char actionStr[ACTION_STRLEN];
//	char stateStr[STATE_STRLEN];
//
//	if (argc != 2) {
//		exit(1);
//	}
//
//	start_connection();
//
//	//srand(time(NULL));
//	srand(8000);
//
//	IterativeDeepeningAI ai;
//	ai.setAI(new NegaScoutAI());
//
//	State * state = new CubeStateImpl();
//	State * app;
//	Action action;
//	bool myMorrisLastTurn = false;
//	uint8 myPawns = 0;
//
//	if (!strcmp(argv[1], "white")) {
//
//		state->setPlayer(PAWN_WHITE);
//		while(1) {
//			action = ai.choose(state);
//			memset(actionStr, 0, sizeof(actionStr));
//			strcpy(actionStr, action.toString().c_str());
//
//			if (send_data(actionStr, ACTION_STRLEN) == FAILURE)
//				exit(1);
//			if (recv_data(stateStr, STATE_STRLEN) == FAILURE)
//				exit(1);
//
//			stateStr[STATE_STRLEN - 1] = '\0';
//			app = state->result(action);
//			delete state;
//			myMorrisLastTurn = app->getMorrisLastTurn(PAWN_WHITE);
//			myPawns = app->getPawnsToPlay(PAWN_WHITE) + app->getPawnsOnBoard(PAWN_WHITE);
//			delete app;
//			state = new CubeStateImpl(stateStr);
//			state->setMorrisLastTurn(PAWN_WHITE, myMorrisLastTurn);
//			state->setMorrisLastTurn(PAWN_BLACK, state->getPawnsToPlay(PAWN_WHITE) + state->getPawnsOnBoard(PAWN_WHITE) < myPawns);
//			state->setPlayer(PAWN_WHITE);
//			cout << state->toNiceString();
//			cout << "\n";
//		}
//	}
//	else if (!strcmp(argv[1], "black")) {
//		while(1) {
//			recv_data(stateStr, STATE_STRLEN);
//			stateStr[STATE_STRLEN - 1] = '\0';
//			cout << stateStr << "\n";
//			cout << "Insert your next move: ";
//			cin >> actionStr;
//			send_data(actionStr, ACTION_STRLEN);
//		}
//	}
//
//}
