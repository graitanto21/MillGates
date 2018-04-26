<<<<<<< HEAD
/*
 * Main.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#include <stdio.h>
#include "State.h"
#include "connection.h"
#include <iostream>

#define ACTION_STRLEN 7
#define STATE_STRLEN 30

using namespace std;

int main(int argc, char* argv[]) {

	char action[ACTION_STRLEN];
	char state[STATE_STRLEN];

	if (argc != 2) {
		exit(1);
	}

	start_connection();

	if (!strcmp(argv[1], "white")) {
		while(1) {
			printf("Insert your next move: /n");
			scanf("%s",action);
			send_data(action, ACTION_STRLEN);
			recv_data(state, STATE_STRLEN);
			state[STATE_STRLEN - 1] = '\0';
			printf("%s\n",state);
		}
	}
	else if (!strcmp(argv[1], "black")) {
		while(1) {
			recv_data(state, STATE_STRLEN);
			state[STATE_STRLEN - 1] = '\0';
			printf("%s\n",state);
			printf("Insert your next move: /n");
			scanf("%s",action);
			send_data(action, ACTION_STRLEN);
		}
	}

}

void debug_1 (void) {

	printf("MillGatesAgent \n");

	State s; //In C++, not necessary to use "new". Here, a new State object is created.

	s.setPawnAt(1, 2, 0, PAWN_BLACK);
	s.setPawnAt(1, 2, 2, PAWN_WHITE);

	//	printf("%s\n",s->toString());
	printf("%s\n",s.toString());

	State* s2 = s.clone();

	printf("%s\n",s2->toString());

	delete s2;

	printf("%s\n",s.toString());

}

=======
///*
// * Main.cpp
// *
// *  Created on: Apr 21, 2018
// *      Author: Luca
// */
//
//#include <stdio.h>
//#include "State.h"
//#include "connection.h"
//#include <iostream>
//
//#define ACTION_STRLEN 7
//#define STATE_STRLEN 30
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//
//	char action[ACTION_STRLEN];
//	char state[STATE_STRLEN];
//
//	if (argc != 2) {
//		exit(1);
//	}
//
//	start_connection();
//
//	if (!strcmp(argv[1], "white")) {
//		while(1) {
//			printf("Insert your next move: /n");
//			scanf("%s",action);
//			send_data(action, ACTION_STRLEN);
//			recv_data(state, STATE_STRLEN);
//			state[STATE_STRLEN - 1] = '\0';
//			printf("%s\n",state);
//		}
//	}
//	else if (!strcmp(argv[1], "black")) {
//		while(1) {
//			recv_data(state, STATE_STRLEN);
//			state[STATE_STRLEN - 1] = '\0';
//			printf("%s\n",state);
//			printf("Insert your next move: /n");
//			scanf("%s",action);
//			send_data(action, ACTION_STRLEN);
//		}
//	}
//
//}
//
//void debug_1 (void) {
//
//	printf("MillGatesAgent \n");
//
//	State s; //In C++, not necessary to use "new". Here, a new State object is created.
//
//	s.setPawnAt(1, 2, 0, PAWN_BLACK);
//	s.setPawnAt(1, 2, 2, PAWN_WHITE);
//
//	//	printf("%s\n",s->toString());
//	printf("%s\n",s.toString());
//
//	State* s2 = s.clone();
//
//	printf("%s\n",s2->toString());
//
//	delete s2;
//
//	printf("%s\n",s.toString());
//
//}
//
>>>>>>> origin/state_work_in_progress
