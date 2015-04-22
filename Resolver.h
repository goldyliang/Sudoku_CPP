/*
 * Resolver.h
 *
 *  Created on: 2014��6��19��
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

	class FillStepWithReverse {
	public:
		FillStepWithReverse(FillStep * step, Board & bd_reverse) : step(step), bd_reverse(bd_reverse)
		{}
		FillStep * step;
		Board bd_reverse;
	};
	Board *bd;

	NumCandStep numCandSteps[COUNT_NUMCANDSTEPS];
	PosCandStep posCandSteps[COUNT_POSCANDSTEPS];
	FillStep * getBestStep(bool & done);

	Stack <FillStepWithReverse*> solve_stack;

	ostream * pDbgInfo;

};

#endif /* RESOLVER_H_ */
