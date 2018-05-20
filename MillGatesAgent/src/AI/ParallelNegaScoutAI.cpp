///*
// * NegaScoutAI.cpp
// *
// *  Created on: May 11, 2018
// *      Author: Luca
// */
//
//#include "ParallelNegaScoutAI.h"
//
//ParallelNegaScoutAI::ParallelNegaScoutAI() {
//	_tables = new ExpVector<HashSet<entry>*>(NUM_CORES);
//	_histories = new ExpVector<HashSet<bool>*>(NUM_CORES);
//	for (int i = 0; i < NUM_CORES; i++) {
//		_tables->add(new HashSet<entry>());
//		_histories->add(new HashSet<bool>());
//	}
//	_hasher = ZobristHashing::getInstance();
//	_depth = MIN_SEARCH_DEPTH;
//	_stopFlag = false;
//	_heuristic = new RomanianHeuristic();
//}
//
//uint8 ParallelNegaScoutAI::getDepth() {
//	return _depth;
//}
//
//void ParallelNegaScoutAI::setDepth(uint8 depth) {
//	_depth = depth;
//}
//
//void ParallelNegaScoutAI::clear() {
//	for (uint8 i = 0; i < NUM_CORES; i++)
//		_tables->get(i)->clear();
//}
//
//void ParallelNegaScoutAI::stop() {
//	_stopFlag = true;
//}
//
//void ParallelNegaScoutAI::addHistory(State * state) {
//	for(int i = 0; i<NUM_CORES; i++) {
//		addHistory(state, i);
//	}
//}
//
//void ParallelNegaScoutAI::addHistory(State * state, int tid) {
//	_histories->get(tid)->add(_hasher->hash(state), true);
//}
//
//void ParallelNegaScoutAI::clearHistory() {
//	for (uint8 i = 0; i < NUM_CORES; i++) {
//		_histories->get(i)->clear();
//	}
//}
//
//void ParallelNegaScoutAI::setMaxFirst(ExpVector<State*> * states,
//		ExpVector<hashcode> * hashes, ExpVector<eval_t> * values,
//		ExpVector<Action> * actions) {
//	// Find max
//	eval_t max = values->get(0);
//	eval_t indexMax = 0;
//	for (eval_t i = 1; i < values->getLogicSize(); i++) {
//		if (values->get(i) > max) {
//			max = values->get(i);
//			indexMax = i;
//		}
//	}
//	if (indexMax != 0) {
//		actions->swap(0, indexMax);
//		states->swap(0, indexMax);
//		hashes->swap(0, indexMax);
//		values->swap(0, indexMax);
//	}
//}
//
//eval_t ParallelNegaScoutAI::negaScout(State * state, hashcode quickhash,
//	uint8 depth, eval_t alpha, eval_t beta, sint8 color, int tid) {
//
//	entry * e;
//	bool presentInTable = _tables->get(tid)->get(quickhash, &e);
//	if (presentInTable && e->depth > depth) {
//		if (e->entryFlag == EXACT)
//			return color * e->eval;
//		if (e->entryFlag == ALPHA_PRUNE && color * e->eval > alpha)
//			alpha = e->eval * color;
//		if (e->entryFlag == BETA_PRUNE && color * e->eval < beta)
//			beta = e->eval * color;
//		if (alpha >= beta)
//			return alpha;
//	}
////	else { //Check in the tables of the other threads (READONLY)
////		for(int i=0; i<NUM_CORES; i++) {
////			if (i!=tid) {
////				presentInTable = _tables->get(i)->get(quickhash, &e);
////				if (presentInTable && e->depth > depth) {
//////					std::cout << "[" << tid << "] Found a match in table " << i << "\n";
////					//Update my table with the entry, so I advantage of the work of the others
////					_tables->get(tid)->add(quickhash, *e);
////					//Then proceeds as above
////					if (e->entryFlag == EXACT)
////						return color * e->eval;
////					if (e->entryFlag == ALPHA_PRUNE && color * e->eval > alpha)
////						alpha = e->eval * color;
////					if (e->entryFlag == BETA_PRUNE && color * e->eval < beta)
////						beta = e->eval * color;
////					if (alpha >= beta)
////						return alpha;
////				}
////			}
////		}
////	}
//
//	eval_t score = 0;
//	bool terminal = state->isTerminal();
//	bool loop = _histories->get(tid)->contains(quickhash) && depth != _depth + 1;
//
//	if (depth == 0 || _stopFlag || loop || terminal) {
//		score = ParallelNegaScoutAI::_heuristic->evaluate(state, terminal,
//				loop);
//		if (!presentInTable)
//			_tables->get(tid)->add(quickhash, entry { depth, EXACT, score });
//		else
//			*e = {depth, EXACT, score};
//		return color * score;
//	}
//
//	ExpVector<Action> * actions = state->getActions();
//	ExpVector<State*> * states = new ExpVector<State*>(actions->getLogicSize());
//	ExpVector<hashcode> * hashes = new ExpVector<hashcode>(
//			actions->getLogicSize());
//	ExpVector<eval_t> * values = new ExpVector<eval_t>(actions->getLogicSize());
//
//	entry * e_tmp;
//
//	bool child_loop, child_present;
//
//	for (eval_t i = 0; i < actions->getLogicSize(); i++) {
//
//		states->add(state->result(actions->get(i)));
//		hashes->add(_hasher->quickHash(state, actions->get(i), quickhash));
//		child_present = _tables->get(tid)->get(hashes->get(i), &e_tmp);
//
//
//		if (child_present && e_tmp->depth > depth - 1)
//			values->add(e_tmp->eval * -color);
//		else {
//			//Check the other tables
//			for(int i=0; i<NUM_CORES; i++) {
//				if (i!=tid) {
//					child_present = _tables->get(i)->get(hashes->get(i), &e_tmp);
//					if (child_present && e_tmp->depth > depth - 1) {
//						values->add(e_tmp->eval * -color);
//						break;
//					}
//				}
//			}
//			if(!child_present) {//Else I have to estimate the value using function
//				child_loop = _histories->get(tid)->contains(hashes->get(i));
//
//				if(!child_loop) { //Check the others
//					for(int i=0; i<NUM_CORES && !child_loop; i++) {
//						if (i!=tid) {
//							child_loop = _histories->get(i)->contains(hashes->get(i));
//							if(child_loop) //Update the history
//								_histories->get(tid)->add(hashes->get(i), child_loop);
//						}
//					}
//				}
//
//				values->add(
//						_heuristic->evaluate(states->get(i),
//								states->get(i)->isTerminal(), child_loop) * -color);
//			}
//		}
//
//	}
//
//	setMaxFirst(states, hashes, values, actions);
//
//	State * child = NULL;
//	hashcode child_hash = 0;
//	entryFlag_parallel_t flag = ALPHA_PRUNE;
//	for (eval_t i = 0; i < actions->getLogicSize(); i++) {
//
//		child = states->get(i);
//		child_hash = hashes->get(i);
//		if (i == 0)
//			score = -negaScout(child, child_hash, depth - 1, -beta, -alpha,
//					-color, tid);
//		else {
//			score = -negaScout(child, child_hash, depth - 1, -alpha - 1, -alpha,
//					-color, tid);
//			if (score > alpha && score < beta)
//				score = -negaScout(child, child_hash, depth - 1, -beta, -score,
//						-color, tid);
//		}
//		delete child;
//		states->set(i, NULL);
//
//		if (score > alpha) {
//			alpha = score;
//			flag = EXACT;
//		}
//
//		if (alpha >= beta) {
//			flag = BETA_PRUNE;
//			break;
//		}
//	}
//	delete actions;
//	delete hashes;
//	for (uint8 i = 0; i < states->getLogicSize(); i++)
//		if (states->get(i) != NULL)
//			delete states->get(i);
//	delete states;
//	delete values;
//
//	if (!presentInTable) {
//		_tables->get(tid)->add(quickhash, entry { depth, flag, (eval_t) (alpha * color) });
////		std::cout << "[" << tid << "] Added: " << quickhash << "\n";
//	}
<<<<<<< HEAD

	eval_t score = 0;
	bool terminal = state->isTerminal();
	bool loop = _histories->get(tid)->contains(quickhash) && depth != _depth + 1;

	if (depth == 0 || _stopFlag || loop || terminal) {
		score = ParallelNegaScoutAI::_heuristic->evaluate(state, terminal,
				loop);
		if (!presentInTable)
			_tables->get(tid)->add(quickhash, entry { depth, EXACT, score });
		else
			*e = {depth, EXACT, score};
		return color * score;
	}

	ExpVector<Action> * actions = state->getActions();
	ExpVector<State*> * states = new ExpVector<State*>(actions->getLogicSize());
	ExpVector<hashcode> * hashes = new ExpVector<hashcode>(
			actions->getLogicSize());
	ExpVector<eval_t> * values = new ExpVector<eval_t>(actions->getLogicSize());

	entry * e_tmp;

	bool child_loop, child_present;

	for (int i = 0; i < actions->getLogicSize(); i++) {

		states->add(state->result(actions->get(i)));
		hashes->add(_hasher->quickHash(state, actions->get(i), quickhash));
		child_present = _tables->get(tid)->get(hashes->get(i), &e_tmp);

		if (child_present && e_tmp->depth > depth - 1)
			values->add(e_tmp->eval * -color);
		else { //Else I have to estimate the value using function
			for(int g=0; g<NUM_CORES; g++) {
				if (g!=tid) {
					child_present = _tables->get(g)->get(hashes->get(i), &e_tmp);
					if (child_present && e_tmp->depth > depth - 1) {
						values->add(e_tmp->eval * -color);
						break;
					}
				}
			}
			if(!child_present) {//Else I have to estimate the value using function
				child_loop = _histories->get(tid)->contains(hashes->get(i));
				//If not present inside my history, check the others
				if(!child_loop) { //Check the others
					for(int f=0; f<NUM_CORES && !child_loop; f++) {
						if (f!=tid) {
							child_loop = _histories->get(f)->contains(hashes->get(i));
							if(child_loop) //If found, update the history
								_histories->get(tid)->add(hashes->get(i), child_loop);
						}
					}
				}
				//Estimate the value
				values->add(_heuristic->evaluate(states->get(i),
								states->get(i)->isTerminal(), child_loop) * -color);
			}
		}
	}

	setMaxFirst(states, hashes, values, actions);

	State * child = NULL;
	hashcode child_hash = 0;
	entryFlag_t flag = ALPHA_PRUNE;
	for (eval_t i = 0; i < actions->getLogicSize(); i++) {

		child = states->get(i);
		child_hash = hashes->get(i);
		if (i == 0)
			score = -negaScout(child, child_hash, depth - 1, -beta, -alpha,
					-color, tid);
		else {
			score = -negaScout(child, child_hash, depth - 1, -alpha - 1, -alpha,
					-color, tid);
			if (score > alpha && score < beta)
				score = -negaScout(child, child_hash, depth - 1, -beta, -score,
						-color, tid);
		}
		delete child;
		states->set(i, NULL);

		if (score > alpha) {
			alpha = score;
			flag = EXACT;
		}

		if (alpha >= beta) {
			flag = BETA_PRUNE;
			break;
		}
	}
	delete actions;
	delete hashes;
	for (uint8 i = 0; i < states->getLogicSize(); i++)
		if (states->get(i) != NULL)
			delete states->get(i);
	delete states;
	delete values;

	if (!presentInTable) {
		_tables->get(tid)->add(quickhash, entry { depth, flag, (eval_t) (alpha * color) });
//		std::cout << "[" << tid << "] Added: " << quickhash << "\n";
	}
	else {
		*e = {depth, flag, (eval_t)(alpha * color)};
//		std::cout << "[" << tid << "] Updated: " << quickhash << "\n";
	}

	return alpha;

}

void * ParallelNegaScoutAI::negaScoutThread_helper(void * param) {
	return (reinterpret_cast<ParallelNegaScoutAI*>(((void**) param)[0]))->negaScoutThread();
}

void * ParallelNegaScoutAI::negaScoutThread() {

	int index = pthread_self()%NUM_CORES;
	int tid = _arguments.tid[index];
	State * state = _arguments.state[index];
	ExpVector<Action> * actions = _arguments.actions[index];
	hashcode hash = _arguments.hash[index];
	sint8 color = _arguments.color[index];
	uint8 depth = _arguments.depth[index];

	// TODO: debug
//	std::cout << "Ciaone, sono il pthread " << index << "\n";
//	for(int i = 0; i < actions->getLogicSize(); i++) {
//		std::cout << actions->get(i) << "\n";
//	}
	//TODO: debug
//
//	//THIS PART EQUALS TO NEGASCOUT
	HashSet<entry> * _table = _tables->get(tid);

	ExpVector<State*> * states = new ExpVector<State*>(actions->getLogicSize());
	ExpVector<hashcode> * hashes = new ExpVector<hashcode>(actions->getLogicSize());
	ExpVector<eval_t> * values = new ExpVector<eval_t>(actions->getLogicSize());


	entry * e_tmp;
	bool child_loop, child_present;

	for (int i = 0; i < actions->getLogicSize(); i++) {
		states->add(state->result(actions->get(i)));
		hashes->add(_hasher->quickHash(state, actions->get(i), hash));
		child_present = _table->get(hashes->get(i), &e_tmp);
		if (child_present && e_tmp->depth > depth - 1)
			values->add(e_tmp->eval * -color);
		else { //Else I have to estimate the value using function
			child_loop = _histories->get(tid)->contains(hashes->get(i));
			values->add(_heuristic->evaluate(states->get(i), states->get(i)->isTerminal(), child_loop)* -color);
		}
	}
	setMaxFirst(states, hashes, values, actions);

	State * child = NULL;
	hashcode child_hash = 0;
	int alpha = -MAX_EVAL_T;
	int beta = MAX_EVAL_T;
	eval_t score = 0;
	for (int i = 0; i < actions->getLogicSize(); i++) {
		child = states->get(i);
		child_hash = hashes->get(i);

		if (i == 0)
			score = -negaScout(child, child_hash, depth - 1, -beta, -alpha,
					-color, tid);
		else {
			score = -negaScout(child, child_hash, depth - 1, -alpha - 1,
					-alpha, -color, tid);
			if (score > alpha && score < beta)
				score = -negaScout(child, child_hash, depth - 1, -beta,
						-score, -color, tid);
		}
		delete child;
		states->set(i, NULL);
	}
	delete hashes;
	for (uint8 i = 0; i < states->getLogicSize(); i++)
		if (states->get(i) != NULL)
			delete states->get(i);
	delete states;
	delete values;

	pthread_exit(NULL);
	return NULL;
}

Action ParallelNegaScoutAI::choose(State * state) {

	_stopFlag = false;

	ExpVector<Action> * actions = state->getActions();

	Action res;
	entry * tempscore;
	hashcode quickhash, hash;

	hash = _hasher->hash(state);
	sint8 color = (state->getPlayer() == PAWN_WHITE) ? 1 : -1;
	eval_t score = - MAX_EVAL_T * color;

	// Thread creation
	void ** param = (void**) malloc(sizeof(void*));
	param[0] = this;

	pthread_t thread[NUM_CORES];
	int rc;
	ExpVector<pthread_t> threads;

	//create the action to give to each thread
	int num_actions_per_thread = (actions->getLogicSize() / NUM_CORES);
	int rest_of_actions = (actions->getLogicSize() % NUM_CORES);
	for (int i = 0; i < NUM_CORES; i++) {
		_arguments.actions[i] = new ExpVector<Action>();
		for (int k = i * num_actions_per_thread;
				k < ((i * num_actions_per_thread) + num_actions_per_thread
								+ ((i == NUM_CORES - 1) ? rest_of_actions : 0));
				k++)
			_arguments.actions[i]->add(actions->get(k));

		_arguments.tid[i] = i;
		_arguments.state[i] = state;
		_arguments.hash[i] = hash;
		_arguments.color[i] = (state->getPlayer() == PAWN_WHITE) ? 1 : -1;
		_arguments.depth[i] = _depth;
		rc = pthread_create(&thread[i], NULL, negaScoutThread_helper,param);
		std::cout << "Avviato thread: " << thread[i] << "\n";
		if (rc) {
			std::cout << "ERRORE: " << rc;
			exit(-1);
		}
	}

	for (int t = 0; t < NUM_CORES; t++) {
		rc = pthread_join(thread[t], NULL);
	}
	for(int j=0; j<NUM_CORES; j++) {
		for (int i = 0; i < actions->getLogicSize(); i++) {
			quickhash = _hasher->quickHash(state, actions->get(i), hash);
			_tables->get(j)->get(quickhash, &tempscore);
			if (tempscore != NULL && color == 1) {
				if (tempscore->eval > score && tempscore->entryFlag == EXACT) {
					score = tempscore->eval;
//					std::cout << "[" << j << "] Score (" << i << "): " << score << "\n";
					res = actions->get(i);
				}
			} else if (tempscore != NULL && color == -1) {
				if (tempscore->eval < score && tempscore->entryFlag == EXACT) {
					score = tempscore->eval;
//					std::cout << "[" << j << "] Score (" << i << "): " << score << "\n";
					res = actions->get(i);
				}

			}
		}
//		std::cout << "Action chosen by " << j << ": " << res << "\n";
	}
	for(int i=0; i<NUM_CORES; i++) {
		delete _arguments.actions[i];
	}
	free(param);
	delete actions;
	return res;
}

void ParallelNegaScoutAI::recurprint(State * state, int depth, int curdepth) {
	entry * val = NULL;
	ExpVector<Action> * actions = state->getActions();
	State * child = NULL;
	for (int j = 0; j < NUM_CORES; j++) {
		std::cout << "TABLE OF THREAD " << j << "\n ==== \n";
		for (int i = 0; i < actions->getLogicSize(); i++) {
			child = state->result(actions->get(i));
			_tables->get(j)->get(_hasher->hash(child), &val);
			if (val == NULL) {
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << actions->get(i) << " -> CUT \n";
			} else if (depth == curdepth) {
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << actions->get(i) << " -> " << (int) val->eval
						<< ", " << (int) val->entryFlag << ", "
						<< (int) val->depth << "\n";
			} else {
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << actions->get(i) << " { \n";
				recurprint(child, depth, curdepth + 1);
				for (int j = 0; j < curdepth; j++)
					std::cout << " | ";
				std::cout << "} -> " << (int) val->eval << ", "
						<< (int) val->entryFlag << ", " << (int) val->depth
						<< "\n";
			}
		}
		delete child;
	}
}

void ParallelNegaScoutAI::print(State * state, int depth) {
	recurprint(state, depth, 0);
}

ParallelNegaScoutAI::~ParallelNegaScoutAI() {
	for (int i = 0; i < NUM_CORES; i++) {
		delete _tables->get(i);
		delete _histories->get(i);
	}
	delete _tables;
	delete _histories;
	delete _heuristic;
}
=======
//	else {
//		*e = {depth, flag, (eval_t)(alpha * color)};
////		std::cout << "[" << tid << "] Updated: " << quickhash << "\n";
//	}
//
//	return alpha;
//
//}
//
//void * ParallelNegaScoutAI::negaScoutThread_helper(void * param) {
//	return (reinterpret_cast<ParallelNegaScoutAI*>(((void**) param)[0]))->negaScoutThread(
//			reinterpret_cast<args*>(((void**) param)[1]));
//}
//
//void * ParallelNegaScoutAI::negaScoutThread(args * arg) {
//
//	int index = pthread_self()%NUM_CORES;
//	int tid = arg->tid[index];
//	State * state = arg->state[index];
//	ExpVector<Action> * actions = arg->actions[index];
//	hashcode hash = arg->hash[index];
//	sint8 color = arg->color[index];
//	uint8 depth = arg->depth[index];
//
//	// TODO: debug
////	std::cout << "Ciaone, sono il pthread " << index << "\n";
////	for(int i = 0; i < actions->getLogicSize(); i++) {
////		std::cout << actions->get(i) << "\n";
////	}
//	//TODO: debug
////
////	//THIS PART EQUALS TO NEGASCOUT
//	HashSet<entry> * _table = _tables->get(tid);
//
//	ExpVector<State*> * states = new ExpVector<State*>(actions->getLogicSize());
//	ExpVector<hashcode> * hashes = new ExpVector<hashcode>(actions->getLogicSize());
//	ExpVector<eval_t> * values = new ExpVector<eval_t>(actions->getLogicSize());
//
//
//	entry * e_tmp;
//	bool child_loop, child_present;
//
//	for (int i = 0; i < actions->getLogicSize(); i++) {
//		states->add(state->result(actions->get(i)));
//		hashes->add(_hasher->quickHash(state, actions->get(i), hash));
//		child_present = _table->get(hashes->get(i), &e_tmp);
//		if (child_present && e_tmp->depth > depth - 1)
//			values->add(e_tmp->eval * -color);
//		else { //Else I have to estimate the value using function
//			child_loop = _histories->get(tid)->contains(hashes->get(i));
//			values->add(_heuristic->evaluate(states->get(i), states->get(i)->isTerminal(), child_loop)* -color);
//		}
//	}
//	setMaxFirst(states, hashes, values, actions);
//
//	State * child = NULL;
//	hashcode child_hash = 0;
//	int alpha = -MAX_EVAL_T;
//	int beta = MAX_EVAL_T;
//	eval_t score = 0;
//	for (int i = 0; i < actions->getLogicSize(); i++) {
//		child = states->get(i);
//		child_hash = hashes->get(i);
//
//		if (i == 0)
//			score = -negaScout(child, child_hash, depth - 1, -beta, -alpha,
//					-color, tid);
//		else {
//			score = -negaScout(child, child_hash, depth - 1, -alpha - 1,
//					-alpha, -color, tid);
//			if (score > alpha && score < beta)
//				score = -negaScout(child, child_hash, depth - 1, -beta,
//						-score, -color, tid);
//		}
//		delete child;
//		states->set(i, NULL);
//	}
//	delete hashes;
//	for (uint8 i = 0; i < states->getLogicSize(); i++)
//		if (states->get(i) != NULL)
//			delete states->get(i);
//	delete states;
//	delete values;
//
//	actions = NULL;
//	delete actions;
//	pthread_exit(NULL);
//	return NULL;
//}
//
//Action ParallelNegaScoutAI::choose(State * state) {
//
//	_stopFlag = false;
//
//	ExpVector<Action> * actions = state->getActions();
//
//	Action res;
//	entry * tempscore;
//	hashcode quickhash, hash;
//
//	hash = _hasher->hash(state);
//	sint8 color = (state->getPlayer() == PAWN_WHITE) ? 1 : -1;
//	eval_t score = - MAX_EVAL_T * color;
//
//	// Thread creation
//	void ** param = (void**) malloc(sizeof(void*) * 2);
//	param[0] = this;
//
//	pthread_t thread[NUM_CORES];
//	int rc;
//	args arguments;
//	ExpVector<pthread_t> threads;
//
//	//create the action to give to each thread
//	ExpVector<Action> * actions_for_thread;
//	int num_actions_per_thread = (actions->getLogicSize() / NUM_CORES);
//	int rest_of_actions = (actions->getLogicSize() % NUM_CORES);
//	for (int i = 0; i < NUM_CORES; i++) {
//		actions_for_thread = new ExpVector<Action>();
//		for (int k = i * num_actions_per_thread;
//				k < ((i * num_actions_per_thread) + num_actions_per_thread
//								+ ((i == NUM_CORES - 1) ? rest_of_actions : 0));
//				k++)
//			actions_for_thread->add(actions->get(k));
//
//		arguments.tid[i] = i;
//		arguments.state[i] = state;
//		arguments.actions[i] = actions_for_thread;
//		arguments.hash[i] = hash;
//		arguments.color[i] = (state->getPlayer() == PAWN_WHITE) ? 1 : -1;
//		arguments.depth[i] = _depth;
//		param[1] = &arguments;
//		rc = pthread_create(&thread[i], NULL, negaScoutThread_helper,param);
//		std::cout << "Avviato thread: " << thread[i] << "\n";
//		if (rc) {
//			std::cout << "ERRORE: " << rc;
//			exit(-1);
//		}
//	}
//
//	for (int t = 0; t < NUM_CORES; t++) {
//		rc = pthread_join(thread[t], NULL);
//	}
//	for(int j=0; j<NUM_CORES; j++) {
//		for (int i = 0; i < actions->getLogicSize(); i++) {
//			quickhash = _hasher->quickHash(state, actions->get(i), hash);
//			_tables->get(j)->get(quickhash, &tempscore);
//			if (tempscore != NULL && color == 1) {
//				if (tempscore->eval > score && tempscore->entryFlag == EXACT) {
//					score = tempscore->eval;
////					std::cout << "[" << j << "] Score (" << i << "): " << score << "\n";
//					res = actions->get(i);
//				}
//			} else if (tempscore != NULL && color == -1) {
//				if (tempscore->eval < score && tempscore->entryFlag == EXACT) {
//					score = tempscore->eval;
////					std::cout << "[" << j << "] Score (" << i << "): " << score << "\n";
//					res = actions->get(i);
//				}
//
//			}
//		}
////		std::cout << "Action chosen by " << j << ": " << res << "\n";
//	}
//	actions_for_thread = NULL;
//	for(int i=0; i<NUM_CORES; i++) {
//		delete arguments.actions[i];
//	}
//	free(param);
//	delete actions;
//	return res;
//}
//
//void ParallelNegaScoutAI::recurprint(State * state, int depth, int curdepth) {
//	entry * val = NULL;
//	ExpVector<Action> * actions = state->getActions();
//	State * child = NULL;
//	for (int j = 0; j < NUM_CORES; j++) {
//		std::cout << "TABLE OF THREAD " << j << "\n ==== \n";
//		for (int i = 0; i < actions->getLogicSize(); i++) {
//			child = state->result(actions->get(i));
//			_tables->get(j)->get(_hasher->hash(child), &val);
//			if (val == NULL) {
//				for (int j = 0; j < curdepth; j++)
//					std::cout << " | ";
//				std::cout << actions->get(i) << " -> CUT \n";
//			} else if (depth == curdepth) {
//				for (int j = 0; j < curdepth; j++)
//					std::cout << " | ";
//				std::cout << actions->get(i) << " -> " << (int) val->eval
//						<< ", " << (int) val->entryFlag << ", "
//						<< (int) val->depth << "\n";
//			} else {
//				for (int j = 0; j < curdepth; j++)
//					std::cout << " | ";
//				std::cout << actions->get(i) << " { \n";
//				recurprint(child, depth, curdepth + 1);
//				for (int j = 0; j < curdepth; j++)
//					std::cout << " | ";
//				std::cout << "} -> " << (int) val->eval << ", "
//						<< (int) val->entryFlag << ", " << (int) val->depth
//						<< "\n";
//			}
//		}
//		delete child;
//	}
//}
//
//void ParallelNegaScoutAI::print(State * state, int depth) {
//	recurprint(state, depth, 0);
//}
//
//ParallelNegaScoutAI::~ParallelNegaScoutAI() {
//	for (int i = 0; i < NUM_CORES; i++) {
//		delete _tables->get(i);
//		delete _histories->get(i);
//	}
//	delete _tables;
//	delete _histories;
//	delete _heuristic;
//}
>>>>>>> 54a6700205a5bcf7ce63f1be2fdc27b82efd9295
