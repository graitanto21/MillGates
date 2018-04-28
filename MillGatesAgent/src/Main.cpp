/*
 * Main.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#include <stdio.h>
#include "State.h"
#include "CubeStateImpl.h"
#include "connection.h"
#include <iostream>

#define ACTION_STRLEN 7
#define STATE_STRLEN 78

using namespace std;
//
int main(int argc, char* argv[]) {

	char action[ACTION_STRLEN];
	char state[STATE_STRLEN];

	if (argc != 2) {
		exit(1);
	}

	start_connection();

	if (!strcmp(argv[1], "white")) {
		while(1) {
			cout << "Insert your next move: ";
			cin >> action;
			send_data(action, ACTION_STRLEN);

			recv_data(state, STATE_STRLEN);
			state[STATE_STRLEN - 1] = '\0';
			State *s = new CubeStateImpl(state);
			cout << "State (internal repr): " << (*s) << "\n";
			cout << "State (ordered repr): ";
			s->toStringToSend();
			cout << "\n";
			delete s; //Ho usato un puntatore, dealloco l'area
		}
	}
	else if (!strcmp(argv[1], "black")) {
		while(1) {
			recv_data(state, STATE_STRLEN);
			state[STATE_STRLEN - 1] = '\0';
			cout << state << "\n";
			cout << "Insert your next move: ";
			cin >> action;
			send_data(action, ACTION_STRLEN);
		}
	}

}
