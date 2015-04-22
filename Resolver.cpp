/*
 * Resolver.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#include "Resolver.h"
#include <iostream>

using std::cout;
using std::endl;

Resolver::Resolver(Board *bd) : bd(bd), pDbgInfo(NULL) {

//	this->bd = bd;

//	pDbgInfo=NULL;

	// Init the number candidate FillSteps for each (x,y) block
	int i=0;
	for (int x=1;x<=9;x++)
		for (int y=1;y<=9;y++)
			numCandSteps[i++].init (bd,x,y);

	i=0;

	// Init the position candidate FillSteps for each column with number 1 to 9
	for (int x=1;x<=9;x++)
		for (int n=1;n<=9;n++)
			posCandSteps[i++].init (bd, bd->getColArea(x), n);

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



			FillStepWithReverse * pStep=new FillStepWithReverse (
					currentStep,*(this->bd));
			currentStep->applyFill();

            if (pDbgInfo)
                bd->print(*pDbgInfo,false,false);

			solve_stack.push (pStep);
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

				FillStepWithReverse * pStep;

				if (solve_stack.pop(pStep)) {
//					currentStep->revertFill();

					currentStep = pStep->step;
					(*this->bd) = pStep->bd_reverse;

					delete pStep;

					if (pDbgInfo) {
						(*pDbgInfo) << "Reverted:";
						currentStep->print(*pDbgInfo);
						bd->print(*pDbgInfo,false,false);
					}

					if (currentStep->next()) {

						if (pDbgInfo) {
							currentStep->print(*pDbgInfo);
						}

						FillStepWithReverse * pStep=new FillStepWithReverse (
								currentStep,*(this->bd));
						currentStep->applyFill();
						solve_stack.push (pStep);

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
