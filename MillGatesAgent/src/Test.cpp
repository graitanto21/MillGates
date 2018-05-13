///*
// * Test.cpp
// *
// *  Created on: 02 mag 2018
// *      Author: Lorenzo Rosa
// */
//
//
//#include "CubeStateImpl.h"
//#include "State.h"
//#include <iostream>
//#include "MinMaxAI.h"
//#include "DummyAI.h"
//#include "NegaScoutAI.h"
//#include "IterativeDeepeningAI.h"
//#include <string.h>
//
//#include "ZobristHashing.h"
//
//State * random_state() {
//	State * result = new CubeStateImpl();
//	uint8 x, y, z, pawn;
//	uint8 n = rand() % 24;
//	for(uint8 i = 0; i < n; i++) {
//		x = rand() % 3;
//		y = rand() % 3;
//		z = rand() % 3;
//		pawn = rand() % 3;
//		if (pawn == 0)
//			pawn = 'O';
//		else if (pawn == 1)
//			pawn = 'W';
//		else
//			pawn = 'B';
//		result->setPawnAt(x, y, z, pawn);
//	}
//	return result;
//}
//
//void testZobristHashing(State * state) {
//
//	//	srand(300);
//	//
//	ZobristHashing * hasher = ZobristHashing::getInstance();
//
//	DummyAI ai;
//	Action a;
//	srand(7200);
//
//	for(int i = 0; i < 20000000; i++) {
//		State * father = random_state();
//		a = ai.choose(father);
//		State * child = father->result(a);
//		if(hasher->hash(child) != hasher->quickHash(father, a, hasher->hash(father))) {
//			std::cout << "Error" << i << "\n";
//		}
//		delete child;
//		delete father;
//		//std::cout << father->toString() << " " << child->toString() << "\n";
//
//	}
//
//	std::cout << "Fine";
//}
//
//void testMinMaxAI(State * state) {
//
//	MinMaxAI ai;
//	srand(400);
//
//	state->setPawnAt2D('c', '5', PAWN_WHITE);
//	state->setPawnAt2D('a', '1', PAWN_BLACK);
//	state->setPawnAt2D('b', '6', PAWN_WHITE);
//	state->setPawnAt2D('d', '2', PAWN_BLACK);
//	state->setPlayer(PAWN_WHITE);
//	state->setPhase(PHASE_1);
//	state->setPawnsToPlay(PAWN_BLACK, 7);
//	state->setPawnsToPlay(PAWN_WHITE, 7);
//	state->setPawnsOnBoard(PAWN_WHITE, 2);
//	state->setPawnsOnBoard(PAWN_BLACK, 2);
//
//	std::cout << ai.choose(state);
//
//}
//
//void testNegaScoutAI(State * state) {
//	NegaScoutAI ai;
//	srand(400);
//
//	//	state->setPawnAt2D('c', '5', PAWN_WHITE);
//	//	state->setPawnAt2D('a', '1', PAWN_BLACK);
//	//	state->setPawnAt2D('b', '6', PAWN_WHITE);
//	//	state->setPawnAt2D('d', '2', PAWN_BLACK);
//	//	state->setPlayer(PAWN_WHITE);
//	//	state->setPhase(PHASE_1);
//	//	state->setPawnsToPlay(PAWN_BLACK, 7);
//	//	state->setPawnsToPlay(PAWN_WHITE, 7);
//	//	state->setPawnsOnBoard(PAWN_WHITE, 2);
//	//	state->setPawnsOnBoard(PAWN_BLACK, 2);
//
//	std::cout << ai.choose(state);
//}
//
//void testMysteryOfFaith(State * state) {
//
//	srand(8000);
//
//	state->setPawnAt2D('a', '1', PAWN_BLACK);
//	state->setPawnAt2D('g', '1', PAWN_BLACK);
//	state->setPawnAt2D('b', '2', PAWN_BLACK);
//	state->setPawnAt2D('d', '3', PAWN_BLACK);
//	state->setPawnAt2D('e', '5', PAWN_BLACK);
//	state->setPawnAt2D('d', '7', PAWN_BLACK);
//	state->setPawnAt2D('g', '7', PAWN_BLACK);
//
//	state->setPawnAt2D('d', '1', PAWN_WHITE);
//	state->setPawnAt2D('g', '4', PAWN_WHITE);
//	state->setPawnAt2D('d', '5', PAWN_WHITE);
//	state->setPawnAt2D('c', '5', PAWN_WHITE);
//	state->setPawnAt2D('b', '6', PAWN_WHITE);
//	state->setPawnAt2D('d', '6', PAWN_WHITE);
//	state->setPawnAt2D('f', '6', PAWN_WHITE);
//	state->setPawnAt2D('a', '7', PAWN_WHITE);
//
//	state->setPawnsToPlay(PAWN_WHITE, 1);
//	state->setPawnsToPlay(PAWN_BLACK, 1);
//	state->setPawnsOnBoard(PAWN_WHITE, 8);
//	state->setPawnsToPlay(PAWN_BLACK, 7);
//
//	state->setPlayer(PAWN_WHITE);
//
//	IterativeDeepeningAI * ai = new IterativeDeepeningAI();
//	ai->setAI(new NegaScoutAI());
//
//	std::cout << ai->choose(state);
//
//
//}
//
//int main(void) {
//
//	State * state;
//
//	/* TESTING THE STATE */
//	//	state = new CubeStateImpl(); //Creates a void state
//	//	testMapping(state);
//	//	delete state;
//	//
//	//Test isInMorris
//	//	state = new CubeStateImpl();
//	//	testIsInMorris(state);
//	//	delete state;
//
//	//Test willBeInMorris
//	//	state = new CubeStateImpl();
//	//	testWillBeInMorris(state);
//	//	delete state;
//
//	//Test getAllPositions
//	//	state = new CubeStateImpl();
//	//	testGetAllPositions(state);
//	//	delete state;
//
//	//	//Test getAvailablePositions
//	//	state = new CubeStateImpl();
//	//	testGetAvailablePositions(state, 'f', '4');
//	//	delete state;
//
//	/* TESTING THE EXPANDER */
//
//	//expand
//	//	state = new CubeStateImpl();
//	//	testExpand(state);
//	//	delete state;
//
//	//PerformAction
//	//	state = new CubeStateImpl();
//	//	testPerformAction(state);
//	//	delete state;
//
//	//ZobristHashing
//	//	state = new CubeStateImpl();
//	//	testZobristHashing(state);
//	//	delete state;
//
//	//AI
//	//	state = new CubeStateImpl();
//	//	testNegaScoutAI(state);
//	//	delete state;
//
//	//Specific test on mystery of faith
//	state = new CubeStateImpl();
//	testMysteryOfFaith(state);
//	delete state;
//
//}
//
