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

#ifndef RESOLVER_STL_
#include "Stack.h"
#else
#include <stack>
#include <vector>
#include <memory>

//#define STACK_T std::stack<FillStepWithReverse, std::vector<FillStepWithReverse>>

#endif

#include "common.h"



class Resolver {
public:
	Resolver(Board *bd);
//	~Resolver();

	bool solve(ostream * pDbgInfo=NULL,  int maxResults=0);

private:

	class FillStepWithReverse {
	public:
		FillStepWithReverse(FillStep & step, Board & bd_reverse) : step(step), bd_reverse(bd_reverse) {};
//		FillStepWithReverse( FillStepWithReverse &&st)  : step(st.step), bd_reverse(std::move(st.bd_reverse)) {};

		FillStep & step;
		Board bd_reverse;
	};

#ifndef RESOLVER_STL_
    typedef FillStepWithReverse* FillStep_Ptr;
    typedef Stack<FillStepWithReverse*> STACK_T;
#else
    typedef shared_ptr<FillStepWithReverse> FillStep_Ptr;
    typedef std::stack<FillStep_Ptr, std::vector<FillStep_Ptr>> STACK_T;
#endif

	Board *bd;

#ifndef RESOLVER_STL_
	// Need improvement to better organize the steps and the algorithm of finding the best step
	NumCandStep numCandSteps[COUNT_NUMCANDSTEPS];
	PosCandStep posCandSteps[COUNT_POSCANDSTEPS];
#else
	typedef vector <FillStep> FillStepList;
	FillStepList FillSteps;
#endif

    FillStep * getBestStep(bool & done);


	STACK_T solve_stack;

	ostream * pDbgInfo;

};

#endif /* RESOLVER_H_ */
