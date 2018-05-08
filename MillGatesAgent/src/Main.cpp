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
//#include "DummyAI.h"
//#include "connection.h"
//#include <iostream>
//#include <time.h>
//
//#define ACTION_STRLEN 7
//#define STATE_STRLEN 82
//
//using namespace std;
////
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
//	srand(time(NULL));
//
//	DummyAI ai;
//
//	if (!strcmp(argv[1], "white")) {
//		State * state = new CubeStateImpl();
//		Action action;
//		while(1) {
//			action = ai.choose(state, PAWN_WHITE);
//
//			actionStr[0] = '\0';
//			actionStr[1] = '\0';
//			actionStr[2] = '\0';
//			actionStr[3] = '\0';
//			actionStr[4] = '\0';
//			actionStr[5] = '\0';
//			actionStr[6] = '\0';
//			strcpy(actionStr, action.toString().c_str());
//
//			send_data(actionStr, ACTION_STRLEN);
//
//			recv_data(stateStr, STATE_STRLEN);
//			stateStr[STATE_STRLEN - 1] = '\0';
//
//			delete state;
//			state = new CubeStateImpl(stateStr);
//			cout << "State (internal repr): " << (state->toString()) << "\n";
//			cout << "State (ordered repr): ";
//			state->toStringToSend();
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
