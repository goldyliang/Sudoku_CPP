/*
 * Resolver.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#include "Resolver.h"
#include <iostream>
#include <utility>
#include <memory>

using std::cout;
using std::endl;


Resolver::Resolver(Board *bd) : bd(bd), pDbgInfo(NULL) {

//	this->bd = bd;

//	pDbgInfo=NULL;
//    std::vector <FillStepWithReverse *> stack_v;
//    this->solve_stack = STACK_T (stack_v);
//    this->solve_stack.

	// Init the number candidate FillSteps for each (x,y) block
	int i=0;
	for (int x=1;x<=9;x++)
		for (int y=1;y<=9;y++)
		{
#ifndef RESOLVER_STL_
            numCandSteps[i++].init (bd,x,y);
#else
            FillSteps.push_back ( NumCandStep(bd,x,y) );
#endif
		}

	i=0;

	// Init the position candidate FillSteps for each column with number 1 to 9
	for (int x=1;x<=9;x++)
		for (int n=1;n<=9;n++)
		{
#ifndef RESOLVER_STL_
			posCandSteps[i++].init (bd, bd->getColArea(x), n);
#else
			FillSteps.push_back ( PosCandStep(bd, bd->getColArea(x), n) );
#endif
		}

	// Init the position candidate FillSteps for each row with number 1 to 9
	for (int y=1;y<=9;y++)
		for (int n=1;n<=9;n++)
			posCandSteps[i++].init (bd, bd->getRowArea(y), n);

	// Init the position candidate FillSteps for each square with number 1 to 9
	for (int x=1;x<=7;x=x+3)
		for (int y=1;y<=7;y=y+3)
			for (int n=1;n<=9;n++)
				posCandSteps[i++].init (bd, bd->getSqrArea(x,y), n);

}


FillStep * Resolver::getBestStep(bool & done) {

	FillStep * best = NULL;
	int minCandNum=10;
	done=true;

#ifndef RESOLVER_STL_
	for (int i=0;i<COUNT_NUMCANDSTEPS;i++)
		if (!numCandSteps[i].solved()) {
			done=false;
			int cnt=numCandSteps[i].candCount();
			if (cnt==0) {
				if (pDbgInfo) {
					(*pDbgInfo) << "NoCand:";
					numCandSteps[i].print(*pDbgInfo);
					(*pDbgInfo) << endl;
				}

				return NULL;
			}
			if (cnt< minCandNum) {
				minCandNum = cnt;
				best = & (numCandSteps[i]);
				if (cnt<=1) break;
			}
		}


	if (minCandNum>1) {
		for (int i=0;i<COUNT_POSCANDSTEPS;i++)
			if (!posCandSteps[i].solved()) {
				done=false;
				int cnt=posCandSteps[i].candCount();
				if (cnt==0) {

					if (pDbgInfo) {
						(*pDbgInfo) << "NoCand:";
						posCandSteps[i].print(*pDbgInfo);
						(*pDbgInfo) << endl;
					}

					return NULL;
				}
				if (cnt < minCandNum) {
					minCandNum = cnt;
					best = & (posCandSteps[i]);
					if (cnt<=1) break;
				}
			}
	}
#else

	auto it = FillSteps.cbegin;
	auto ed = FillSteps.cend;

	while (it!=ed)
	{
        FillStep &st = *it;

	    if (st.solved()) {
            done=false;
            int cnt=st.candCount();
            if (cnt==0) {
                if (pDbgInfo) {
                    (*pDbgInfo) << "NoCand:";
                    numCandSteps[i].print(*pDbgInfo);
                    (*pDbgInfo) << endl;
                }

                return NULL;
            }
            if (cnt< minCandNum) {
                minCandNum = cnt;
                best = & (st);
                if (cnt<=1) break;
            }
        }
    }

#endif

	return best;
}

bool Resolver::solve(ostream * pDbgInfo, int maxResults) {

	int resultNum=0;

	this->pDbgInfo = pDbgInfo;

	bool finished=false;

	while (!finished)
	{
		// Find the best fill step to go
		bool done;

		FillStep * currentStep = getBestStep(done);

		if (!done && currentStep) {
			currentStep->first();
			if (pDbgInfo)
				currentStep->print(*pDbgInfo);


#ifndef RESOLVER_STL_

			FillStepWithReverse * pStep=new FillStepWithReverse (
					*currentStep,*(this->bd));
#else
			auto pStep = std::make_shared<FillStepWithReverse> (
			        *currentStep,*(this->bd));
#endif

//			FillStepWithReverse stepRev(*currentStep, *(this->bd));
			currentStep->applyFill();

            if (pDbgInfo)
            {
                bd->print(*pDbgInfo,false,false);
                /*
                cout<< "stepRev.bd before push" << endl;
                stepRev.bd_reverse.print (*pDbgInfo,false,false);*/
            }

//            cout << &(this->bd->[1][1]);
//			solve_stack.push (std::move(stepRev));
            //To optimize: only need push if the current step has more than one candidates
            solve_stack.push (pStep);

			/*
			if (pDbgInfo)
			{
			    (*pDbgInfo) << "After push" << endl;
			    //bd->print(*pDbgInfo,false,false);
			    solve_stack.top().bd_reverse.print(*pDbgInfo,false,false);
			}*/

//            cout << &(this->bd[1][1]);
//            cout << &(solve_stack.top().bd_reverse.bd[1][1]);

		} else {

			if (done) {
				cout << "Result #" << ++resultNum << endl;
				bd->print(cout,false,false);

				if (maxResults>0 && resultNum>=maxResults) {
					cout << "Not all results showed..." << endl;
					finished = true;
				}
			}

			bool need_revert=true;

			while (need_revert){
				currentStep=NULL;

				if (!solve_stack.empty()) {

				    /*
				    if (pDbgInfo) {
				        *pDbgInfo << "Stack top before moving" <<endl;
				        solve_stack.top().bd_reverse.print(*pDbgInfo,false,false);
				    }*/

//	                FillStepWithReverse stepRev = std::move(solve_stack.top()); //* pStep;

				    FillStep_Ptr pStep = solve_stack.top();

	                /*
                    if (pDbgInfo) {
                        *pDbgInfo << "stepRev after moving" <<endl;
                        stepRev.bd_reverse.print(*pDbgInfo,false,false);
                        *pDbgInfo << "Stack top after moving" <<endl;
                        solve_stack.top().bd_reverse.print(*pDbgInfo,false,false);
                    }*/

				    solve_stack.pop();


//					currentStep->revertFill();

					//currentStep = &stepRev.step;
					currentStep = &pStep->step;
					(*this->bd) = pStep->bd_reverse;
					//(*this->bd) = stepRev.bd_reverse;
					//(*this->bd) = std::move(stepRev.bd_reverse); // pStep->bd_reverse;

#ifndef RESOLVER_STL_
					delete pStep;
#endif

					if (pDbgInfo) {
						(*pDbgInfo) << "Reverted:";
						currentStep->print(*pDbgInfo);
						bd->print(*pDbgInfo,false,false);
					}

					if (currentStep->next()) {

						if (pDbgInfo) {
							currentStep->print(*pDbgInfo);
						}

						/*FillStepWithReverse * pStep=new FillStepWithReverse (
								currentStep,*(this->bd));
						currentStep->applyFill();
						solve_stack.push (pStep); */

#ifndef RESOLVER_STL_

						FillStepWithReverse * pStep=new FillStepWithReverse (
						        *currentStep,*(this->bd));
#else
						auto pStep = std::make_shared<FillStepWithReverse> (
						        *currentStep,*(this->bd));
#endif

			            // FillStepWithReverse stepRev(*currentStep, *(this->bd));
			            currentStep->applyFill();

			            solve_stack.push (pStep);
			            //solve_stack.push (std::move(stepRev));

			            if (pDbgInfo)
	                        if (pDbgInfo)
	                            bd->print(*pDbgInfo,false,false);

						need_revert=false;
					}
				} else break;
			};

			if (!currentStep) {
				cout << "All results showed. Total " << resultNum << endl;
				finished=true; // no result
			}
		}
	}

	return (resultNum>0);
}
