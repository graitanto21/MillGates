/*
 * Test.cpp
 *
 *  Created on: 02 mag 2018
 *      Author: Lorenzo Rosa
 */


#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "../AI/DummyAI.h"
#include "../AI/Hash/ZobristHashing.h"
#include "../AI/IterativeDeepeningAI.h"
#include "../AI/MinMaxAI.h"
#include "../AI/NegaScoutAI.h"
#include "../Domain/CubeStateImpl.h"
#include "../Domain/State.h"
#include "../Utils/HashSet.h"

State * random_state() {
	State * result = new CubeStateImpl();
	State * temp;
	ExpVector<Action> * actions;
	int n = 3 + rand() % 50;
	for (int i = 0; i < n && !result->isTerminal(); i++) {
		temp = result;
		actions = result->getActions();
		result = temp->result(actions->get(rand() % actions->getLogicSize()));
		delete temp;
		delete actions;
	}
	return result;
}

void testZobristHashing(State * state) {

	//	srand(300);
	//
	ZobristHashing * hasher = ZobristHashing::getInstance();

	DummyAI ai;
	Action a;
	srand(7200);
	State * father;
	State * child;

	for(int i = 0; i < 200000; i++) {
		father = random_state();
		if (father->isTerminal()) {
			delete father;
			continue;
		}
		a = ai.choose(father);
		child = father->result(a);
		if(hasher->hash(child) != hasher->quickHash(father, a, hasher->hash(father))) {
			std::cout << "Error" << i << "\n";
		}
		delete child;
		delete father;
		//std::cout << father->toString() << " " << child->toString() << "\n";

	}

	std::cout << "Fine";
}

void testMinMaxAI(State * state) {

	MinMaxAI ai;
	srand(400);

	state->setPawnAt2D('c', '5', PAWN_WHITE);
	state->setPawnAt2D('a', '1', PAWN_BLACK);
	state->setPawnAt2D('b', '6', PAWN_WHITE);
	state->setPawnAt2D('d', '2', PAWN_BLACK);
	state->setPlayer(PAWN_WHITE);
	state->setPawnsToPlay(PAWN_BLACK, 7);
	state->setPawnsToPlay(PAWN_WHITE, 7);
	state->setPawnsOnBoard(PAWN_WHITE, 2);
	state->setPawnsOnBoard(PAWN_BLACK, 2);

	std::cout << ai.choose(state);

}

void testNegaScoutAI(State * state) {
	ParallelNegaScoutAI ai;
	srand(400);

	pawn player = PAWN_BLACK;

	state->setPawnAt2D('d', '3', OPP(player));
	state->setPawnAt2D('e', '3', OPP(player));
	state->setPawnAt2D('c', '4', OPP(player));
	state->setPawnAt2D('f', '4', OPP(player));
	state->setPawnAt2D('e', '5', OPP(player));
	state->setPawnAt2D('f', '6', OPP(player));

	state->setPawnAt2D('c', '3', player);
	state->setPawnAt2D('c', '5', player);
	state->setPawnAt2D('d', '7', player);

	state->setPlayer(player);
	state->setPawnsToPlay(OPP(player), 0);
	state->setPawnsToPlay(player, 0);
	state->setPawnsOnBoard(player, 3);
	state->setPawnsOnBoard(OPP(player), 6);

	ai.setDepth(2);
	std::cout << ai.choose(state) << "\n\n";

	state->print();

	std::cout << "DEPTH 0" << "\n\n";
	ai.print(state, 0);
	std::cout << "DEPTH 1" << "\n\n";
	ai.print(state, 1);
	std::cout << "DEPTH 2" << "\n\n";
	ai.print(state, 2);
//	std::cout << "DEPTH 3" << "\n\n";
//	ai.print(state, 3);
//	std::cout << "DEPTH 4" << "\n\n";
//	ai.print(state, 4);
//	std::cout << "DEPTH 5" << "\n\n";
//	ai.print(state, 5);
//	std::cout << "DEPTH 6" << "\n\n";
//	ai.print(state, 6);
}

void testIterativeDeepeningAI(State * state) {

	srand(8000);

	state->setPlayer(PAWN_WHITE);

	IterativeDeepeningAI * ai = new IterativeDeepeningAI();
	ai->setAI(new ParallelNegaScoutAI());

	ai->choose(state);
	ai->choose(state);

}

void testMorrisCount(State * state) {

	state->setPawnAt2D('a', '1', PAWN_WHITE);
	state->setPawnAt2D('a', '4', PAWN_WHITE);
	state->setPawnAt2D('a', '7', PAWN_WHITE);
	state->setPawnAt2D('b', '2', PAWN_WHITE);
	state->setPawnAt2D('b', '4', PAWN_WHITE);
	state->setPawnAt2D('b', '6', PAWN_WHITE);
	state->setPawnAt2D('c', '3', PAWN_WHITE);
	state->setPawnAt2D('c', '4', PAWN_WHITE);
	state->setPawnAt2D('c', '5', PAWN_WHITE);

	std::cout << (int)state->morrisCount(PAWN_WHITE);
}

void testBlockedPawns(State * state) {

	state->setPawnAt2D('a', '1', PAWN_BLACK);
	state->setPawnAt2D('a', '7', PAWN_WHITE);
	state->setPawnAt2D('a', '4', PAWN_BLACK);
	state->setPawnAt2D('b', '4', PAWN_BLACK);
	state->setPawnAt2D('b', '2', PAWN_BLACK);
	state->setPawnAt2D('d', '2', PAWN_WHITE);
	state->setPawnAt2D('d', '1', PAWN_WHITE);

	std::cout << (int)state->blockedPawnCount(PAWN_BLACK);

}

void testPotentialMorrises(State * state) {

	state->setPawnAt2D('d', '1', PAWN_BLACK);
	state->setPawnAt2D('b', '2', PAWN_BLACK);
	state->setPawnAt2D('f', '2', PAWN_BLACK);
	state->setPawnAt2D('d', '3', PAWN_BLACK);

	std::cout << (int)state->potentialMorrisCount(PAWN_BLACK);

}

void testPotentialDoubleMorrises(State * state) {
	state->setPawnAt2D('a', '1', PAWN_BLACK);
	state->setPawnAt2D('a', '7', PAWN_BLACK);
	state->setPawnAt2D('d', '7', PAWN_BLACK);
	state->setPawnAt2D('d', '1', PAWN_BLACK);

	std::cout << (int)state->potentialDoubleMorrisCount(PAWN_BLACK);
}

void testDoubleMorrisesCount(State * state) {

	state->setPawnAt2D('a', '1', PAWN_BLACK);
	state->setPawnAt2D('a', '4', PAWN_BLACK);
	state->setPawnAt2D('a', '7', PAWN_BLACK);
	state->setPawnAt2D('d', '1', PAWN_BLACK);
	state->setPawnAt2D('g', '1', PAWN_BLACK);
	state->setPawnAt2D('g', '4', PAWN_BLACK);
	state->setPawnAt2D('g', '7', PAWN_BLACK);
	state->setPawnAt2D('d', '7', PAWN_BLACK);

	std::cout << (int)state->doubleMorrisCount(PAWN_BLACK) << "\n";

}

void testOrdering(State * state) {
	state->setPawnAt2D('a', '1', PAWN_WHITE);
	state->setPawnAt2D('a', '7', PAWN_WHITE);
	state->setPawnAt2D('d', '7', PAWN_BLACK);
	state->setPawnAt2D('d', '1', PAWN_BLACK);
	state->setPawnsOnBoard(PAWN_WHITE, 2);
	state->setPawnsOnBoard(PAWN_BLACK, 2);

	RomanianHeuristic h;
	ExpVector<Action> * actions = state->getActions();
	State * child = NULL;
	for(int i = 0; i < actions->getLogicSize(); i++){
		std::cout << actions->get(i) << "(";
		child = state->result(actions->get(i));
		std::cout << h.evaluate(child, false, false) << ") ";
	}
	std::cout << "\n";
	ParallelNegaScoutAI ai;
	ExpVector<State*> * states = new ExpVector<State*>(actions->getLogicSize());
	for(eval_t i = 0; i < actions->getLogicSize(); i++){
		states->add(state->result(actions->get(i)));
	}
	ExpVector<hashcode> * hashes = new ExpVector<hashcode>(actions->getLogicSize());
	for(eval_t i=0; i<actions->getLogicSize(); i++) {
		hashes->add(ZobristHashing::getInstance()->quickHash(state, actions->get(i), ZobristHashing::getInstance()->hash(state)));
	}
	ExpVector<eval_t> * values = new ExpVector<eval_t>(actions->getLogicSize());
	for(eval_t i=0; i<actions->getLogicSize(); i++) {
		values->add(h.evaluate(states->get(i), false, false) * 1);
	}
	//ai.quickSort(state, states, hashes, values, actions, 0, actions->getLogicSize()-1, 1, ZobristHashing::getInstance()->hash(state));
	std::cout << "\n" << "NEW:\n";
	for(int i = 0; i < actions->getLogicSize(); i++){
		std::cout << actions->get(i) << "(";
		child = state->result(actions->get(i));
		std::cout << h.evaluate(child, false, false) << ") ";
	}
	std::cout << "\nSize: " << states->getLogicSize()<<"\n";
	State * ch = NULL;
	for(int i = 0; i < states->getLogicSize(); i++){
		ch = states->get(i);
		std::cout << ch->toString() << " ";
	}
	delete actions;
	for(int i = 0; i < states->getLogicSize(); i++)
		delete states->get(i);
	delete states;
	delete hashes;


}

void testHashTable() {

	HashSet<int> * hashTable = new HashSet<int>;

	int * val = new int();
	*val = 10;
	int * val2 = new int();
	*val2 = 30;

	hashTable->add(100, 223);
	hashTable->add(167772214, 222);

	hashTable->get(100, &val);
	hashTable->get(167772214, &val2);

	std::cout << *val << "\n";
	std::cout << *val2 << "\n";
}

/*

7 W--------O--------O
6 |--B-----O-----B--|
5 |--|--O--O--O--|--|
4 W--B--O     O--W--W
3 |--|--O--O--O--|--|
2 |--O-----W-----O--|
1 B--------O--------O
 a  b  c  d  e  f  g

 */

void testRomanianHeuristic() {

	srand(time(NULL));

	State * state;

	for (int i = 0; i < 1000; i++) {
		state = random_state();

		state->print();

		delete state;
	}


}

void testParallelNegaScoutAI(State * state) {
	ParallelNegaScoutAI ai;
	srand(400);

	pawn player = PAWN_WHITE;

	state->setPawnAt2D('d', '3', OPP(player));
	state->setPawnAt2D('e', '3', OPP(player));
	state->setPawnAt2D('c', '4', OPP(player));
	state->setPawnAt2D('f', '4', OPP(player));
	state->setPawnAt2D('e', '5', OPP(player));
	state->setPawnAt2D('f', '6', OPP(player));

	state->setPawnAt2D('c', '3', player);
	state->setPawnAt2D('c', '5', player);
	state->setPawnAt2D('d', '7', player);

	state->setPlayer(player);
	state->setPawnsToPlay(OPP(player), 0);
	state->setPawnsToPlay(player, 0);
	state->setPawnsOnBoard(player, 3);
	state->setPawnsOnBoard(OPP(player), 6);

	ai.setDepth(2);

	ExpVector<Action> * actions = state->getActions();
	std::cout << "Azioni disponibili: "<< actions->getLogicSize() << "\n";
	for (eval_t i = 0; i < actions->getLogicSize(); i++) {
		std::cout << actions->get(i) << " ";
	}
	std::cout << "\n";

	std::cout << "\nChosen action: " << ai.choose(state) << "\n\n";

//	state->print();
//
//	std::cout << "DEPTH 0" << "\n\n";
//	ai.print(state, 0);
//	std::cout << "DEPTH 1" << "\n\n";
//	ai.print(state, 1);
//	std::cout << "DEPTH 2" << "\n\n";
//	ai.print(state, 2);
//	std::cout << "DEPTH 3" << "\n\n";
//	ai.print(state, 3);
//	std::cout << "DEPTH 4" << "\n\n";
//	ai.print(state, 4);
//	std::cout << "DEPTH 5" << "\n\n";
//	ai.print(state, 5);
//	std::cout << "DEPTH 6" << "\n\n";
//	ai.print(state, 6);
}

void testParallelIterativeDeepeningAI(State * state) {

	IterativeDeepeningAI ai;
	ai.setAI(new ParallelNegaScoutAI());

	Action action;

	srand(400);

	pawn player = PAWN_WHITE;

	//State blank
	state->setPlayer(player);
	state->setPawnsToPlay(OPP(player), 9);
	state->setPawnsToPlay(player, 9);
	state->setPawnsOnBoard(player, 0);
	state->setPawnsOnBoard(OPP(player), 0);

	std::cout << "\nChosen action: " << ai.choose(state) << "\n\n";

}

#if defined(DEBUG)
int main(void) {

	State * state = new CubeStateImpl();

<<<<<<< HEAD
	testZobristHashing(state);
=======
	//testZobristHashing(state);
>>>>>>> parallel_negascout
	//testNegaScoutAI(state);
	//testIterativeDeepeningAI(state);
	//testMorrisCount(state);
	//testBlockedPawns(state);
	//testPotentialMorrises(state);
	//testPotentialDoubleMorrises(state);
	//testDoubleMorrisesCount(state);
	//testOrdering(state);
	//testHashTable();
<<<<<<< HEAD
	testRomanianHeuristic();

=======
	//testRomanianHeuristic();
	//testParallelNegaScoutAI(state);
	testParallelIterativeDeepeningAI(state);
>>>>>>> parallel_negascout
	delete state;

}
#endif

