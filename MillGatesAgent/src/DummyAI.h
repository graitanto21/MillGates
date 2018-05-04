/*
 * DummyAI.h
 *
 *  Created on: May 4, 2018
 *      Author: Luca
 */

#ifndef DUMMYAI_H_
#define DUMMYAI_H_

#include "AI.h"

class DummyAI : public AI{
public:
	DummyAI();
	virtual ~DummyAI();

	virtual Action choose(Node node);
};

#endif /* DUMMYAI_H_ */
