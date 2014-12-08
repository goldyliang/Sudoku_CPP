/*
 * Resolver.h
 *
 *  Created on: 2014Äê6ÔÂ19ÈÕ
 *      Author: Liang
 */

#ifndef RESOLVER_H_
#define RESOLVER_H_

#include "Board.h"
#include "FillStep.h"
#include "Stack.h"

#define COUNT_NUMCANDSTEPS 81  // 9*9
#define COUNT_POSCANDSTEPS (27*9)

class Resolver {
public:
	Resolver(Board *bd);
//	~Resolver();

	bool solve(ostream * pDbgInfo=NULL,  int maxResults=0);

private:
	Board *bd;

	NumCandStep numCandSteps[COUNT_NUMCANDSTEPS];
	PosCandStep posCandSteps[COUNT_POSCANDSTEPS];
	FillStep * getBestStep(bool & done);

	Stack <FillStep*> solve_stack;

	ostream * pDbgInfo;

};

#endif /* RESOLVER_H_ */
