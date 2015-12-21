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
#include <pthread.h>

//#define STACK_T std::stack<FillStepWithReverse, std::vector<FillStepWithReverse>>

#endif

#include "common.h"



class Resolver {
public:
	Resolver(Board *bd);
//	~Resolver();

	bool solve(ostream * pDbgInfo=NULL,  bool bStatInfo=false, int maxResults=0);



private:

//    void updateFillable(NUM_T x, NUM_T y, NUM_T n);
//    void markUnFillable(NUM_T x, NUM_T y, NUM_T n);


#ifndef RESOLVER_STL_
    // Need improvement to better organize the steps and the algorithm of finding the best step
    NumCandStep numCandSteps[COUNT_NUMCANDSTEPS];
    PosCandStep posCandSteps[COUNT_POSCANDSTEPS];
#else
//    typedef vector < FillStep_Ptr > FillStepList;
    FillStepList FillSteps;
#endif

	class FillStepWithReverse {
	public:

//		FillStepWithReverse( FillStepWithReverse &&st)  : step(st.step), bd_reverse(std::move(st.bd_reverse)) {};

        FillStepWithReverse(Board & bd, FillStepList & FillSteps);

		Board bd_reverse;

		FillStepList FillSteps_reverse;

	};

#ifndef RESOLVER_STL_
    typedef FillStepWithReverse* FillStep_Ptr;
    typedef Stack<FillStepWithReverse*> STACK_T;
#else
    typedef shared_ptr<FillStepWithReverse> FillStepRev_Ptr;
    typedef std::stack<FillStepRev_Ptr, std::vector<FillStepRev_Ptr>> STACK_T;
#endif
    STACK_T solve_stack;


	Board bd;
//    ARRAY_9_9_T <NumList> candList;
//    std::array<Area, 3*9> areas;

//    FillStep * getBestStep(bool & done);
//    void updateStatInfo (NUM_T x, NUM_T y, NUM_T n);
    bool fillStep();
//    Area * getRowArea(NUM_T y);
//    Area * getColArea(NUM_T x);
//    Area * getSqrArea(NUM_T x, NUM_T y);
//    void   getThreeAreas(NUM_T x, NUM_T y, Area* ars[]);

//    void printStatInfo (ostream & os, bool cand, bool area);
//    NumList * getFillableList (NUM_T x, NUM_T y);



	ostream * pDbgInfo;

    int cPush;
    int cPop;

    static unsigned getMaxThreads();
    static unsigned cAvailThreads; // will get initialized when the first object created
    pthread_mutex_t mtxAvailThreads;

    friend class FillStep;
    friend class NumCandStep;
    friend class PosCandStep;

};

#endif /* RESOLVER_H_ */
