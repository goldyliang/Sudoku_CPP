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
#include <algorithm>

using std::cout;
using std::endl;


Resolver::Resolver(Board *p_bd) : FillSteps(), pDbgInfo(NULL), cPush(0), cPop(0) {

//	this->bd = bd;

//	pDbgInfo=NULL;
//    std::vector <FillStepWithReverse *> stack_v;
//    this->solve_stack = STACK_T (stack_v);
//    this->solve_stack.

    /* Fill the initial board and update status */

    for (NUM_T x=1;x<=9;x++)
        for (NUM_T y=1;y<=9;y++)
            if (p_bd->bd[x][y]) {
                bd.bd[x][y] = p_bd->bd[x][y];
                FillSteps.updateSteps (x,y, bd.bd[x][y]);

//               bd.print(cout);
 //              FillSteps.printInfo(cout);

                //PosCandStep::updateSteps (x,y, bd.bd[x][y]);
                //updateStatInfo (x,y,bd->bd[x][y]);
            }

    if (pDbgInfo)
    {
        bd.print(*pDbgInfo);
        FillSteps.printInfo(*pDbgInfo);
    }



/*
	// Init the number candidate FillSteps for each (x,y) block
#ifndef RESOLVER_STL_
    int i=0;
#endif

	for (int x=1;x<=9;x++)
		for (int y=1;y<=9;y++)
		{
#ifndef RESOLVER_STL_
            numCandSteps[i++].init (bd,x,y);
#else
            //NumCandStep st(bd,x,y);
            //st.print(cout);
            FillSteps.push_back ( std::make_shared <NumCandStep> (bd,x,y) );
#endif
		}

#ifndef RESOLVER_STL_
    i=0;
#endif

	// Init the position candidate FillSteps for each column with number 1 to 9
	for (int x=1;x<=9;x++)
		for (int n=1;n<=9;n++)
		{
#ifndef RESOLVER_STL_
			posCandSteps[i++].init (bd, bd->getColArea(x), n);
#else
			FillSteps.push_back ( std::make_shared <PosCandStep> (bd, bd->getColArea(x), n) );
#endif
		}

	// Init the position candidate FillSteps for each row with number 1 to 9
	for (int y=1;y<=9;y++)
		for (int n=1;n<=9;n++)
		{
#ifndef RESOLVER_STL_
			posCandSteps[i++].init (bd, bd->getRowArea(y), n);
#else
            FillSteps.push_back ( std::make_shared <PosCandStep> (bd, bd->getRowArea(y), n) );
#endif
		}

	// Init the position candidate FillSteps for each square with number 1 to 9
	for (int x=1;x<=7;x=x+3)
		for (int y=1;y<=7;y=y+3)
			for (int n=1;n<=9;n++)
			{
#ifndef RESOLVER_STL_
			    posCandSteps[i++].init (bd, bd->getSqrArea(x,y), n);
#else
	            FillSteps.push_back ( std::make_shared <PosCandStep> (bd, bd->getSqrArea(x,y), n) );
#endif
			}
*/

#ifdef FILLSTEP_DYNAMIC_SORT_
	sort( FillSteps.begin(), FillSteps.end(),
	        [] (const FillStep_Ptr &a, const FillStep_Ptr &b)
	        {
	            NUM_T ca=a->candCount();
	            NUM_T cb=b->candCount();

	            if (ca==0)
	                return false;  //Put items with zero to the end instead of head
	            else if (cb==0)
	                return true;
	            else
	                return ca < cb; } );
#endif

/*	auto it=FillSteps.begin();
	while (it!=FillSteps.end())
	{
	    cout << (*it)->candCount() << ",";
	    it++;
	}
	cout << endl;*/

}

/*Area * Resolver::getRowArea(NUM_T y)
{
    return &areas[y-1];
}

Area * Resolver::getColArea(NUM_T x)
{
    return &areas[x+8];
}

Area * Resolver::getSqrArea(NUM_T x, NUM_T y)
{
    NUM_T xx=(x-1)/3;  //0,1,2
    NUM_T yy=(y-1)/3;

    return &areas[18+yy*3+xx];
}

void Resolver::getThreeAreas(NUM_T x, NUM_T y, Area* ars[])
{
    ars[0]=getRowArea(y);
    ars[1]=getColArea(x);
    ars[2]=getSqrArea(x,y);
}
*/

/*NumList * Resolver::getFillableList (NUM_T x, NUM_T y)
{
  return &(candList[x][y]);
}

void Resolver::markUnFillable(NUM_T x, NUM_T y, NUM_T n)
{
    candList[x][y].remove(n);

    Area * ars[3];
    getThreeAreas(x,y,ars);

    for (NUM_T ari=0;ari<3;ari++)
    {
        NUM_T i;
        ars[ari]->getPosIdx(x,y,i);
        ars[ari]->getNumPosList(n)->remove(i);
    }
}

void Resolver::updateFillable(NUM_T x, NUM_T y, NUM_T n)
{
    Area * ars[3];
    getThreeAreas(x,y,ars);

    bool fillable=true;

    if (bd->bd[x][y]>0)
        fillable=false;
    else
        for (NUM_T ari=0;ari<3;ari++)
        {
            Area * ar=ars[ari];
            for (NUM_T i=1;i<=9;i++)
            {
                NUM_T tx,ty;
                ar->getPos(i,tx,ty);
                if (bd->bd[tx][ty]==n) {
                    fillable=false;
                    break;
                }
            }
        }

    if (fillable) {
        candList[x][y].add(n);

        for (NUM_T ari=0;ari<3;ari++)
        {
            Area * ar=ars[ari];
            NUM_T i;
            ar->getPosIdx(x,y,i);
            ar->getNumPosList(n)->add(i);
        }
    }
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

	auto it = FillSteps.begin();
	auto ed = FillSteps.end();

	//return *it;

	while (it!=ed)
	{
        FillStep &st = **it++;

	    if (!st.solved()) {
            done=false;
            int cnt=st.candCount();
            if (cnt==0) {
                if (pDbgInfo) {
                    (*pDbgInfo) << "NoCand:";
                    st.print(*pDbgInfo);
                    (*pDbgInfo) << endl;
                }

                return NULL;
            }

#ifdef FILLSTEP_DYNAMIC_SORT_
            best = & (st);
            break;
#else

            if (cnt< minCandNum) {
                minCandNum = cnt;
                best = & (st);

                if (cnt<=1)
                    break;
            }
#endif

	    }
    }

#endif

	return best;
}

void Resolver::updateStatInfo (NUM_T x, NUM_T y, NUM_T n)
{
    for (NUM_T nn=1;nn<=9;nn++)
        markUnFillable(x,y,nn); //candList[x][y].remove(n);

    Area * ars[3];
    getThreeAreas(x,y,ars);

    for (NUM_T ari=0;ari<3;ari++)
    {
        Area * ar=ars[ari];
        for (NUM_T i=1;i<=9;i++)
        {
            NUM_T tx,ty;
            ar->getPos(i,tx,ty);
            markUnFillable(tx,ty,n);
        }
    }
} */

Resolver::FillStepWithReverse::FillStepWithReverse(Board & bd, FillStepList & FillSteps) :
         bd_reverse(bd)
        , FillSteps_reverse(FillSteps)
{
};

bool Resolver::fillStep() {

    FillStep* currentStep = FillSteps.getCurrentStep();

    NUM_T x = currentStep->x;
    NUM_T y = currentStep->y;
    NUM_T n = currentStep->n;

   // if (!candList[x][y].in(n)) return false;

    if (pDbgInfo)
        currentStep->print(*pDbgInfo);


//there is a problem if always push the steps... why????
    if (!currentStep->isLast())
    {
#ifndef RESOLVER_STL_

            FillStepWithReverse * pStep=new FillStepWithReverse (
                    *currentStep,*(this->bd));
#else
#ifdef RESOLVER_FAST_REVERSE_
        auto pStep = std::make_shared<FillStepWithReverse> (
                this->bd,this->FillSteps);
#else
        auto pStep = std::make_shared<FillStepWithReverse> (
                *currentStep);
#endif
#endif

        if (this->pDbgInfo)
        {
            *pDbgInfo << "to be pushed" << endl;

            this->bd.print (*pDbgInfo);
            this->FillSteps.printInfo(*pDbgInfo);

            cout << "pushed" << endl;

            pStep->bd_reverse.print(*pDbgInfo);
            pStep->FillSteps_reverse.printInfo(*pDbgInfo);
        }

        //            cout << &(this->bd->[1][1]);
        //          solve_stack.push (std::move(stepRev));
                    //To optimize: only need push if the current step has more than one candidates
        solve_stack.push (pStep);

        cPush++;
    }

//          FillStepWithReverse stepRev(*currentStep, *(this->bd));
    currentStep->applyFill(bd);

    if (!FillSteps.updateSteps(x,y,n))
        return false; // this step leads to invalid

    //updateStatInfo(x,y,n);

#ifdef FILLSTEP_DYNAMIC_SORT_
    sort( FillSteps.begin(), FillSteps.end(),
            [] (const FillStep_Ptr &a, const FillStep_Ptr &b)
            { return a->candCount() < b->candCount(); } );
#endif

    if (pDbgInfo)
    {
        bd.print(*pDbgInfo);
        //this->print(false,false);
        /*
        cout<< "stepRev.bd before push" << endl;
        stepRev.bd_reverse.print (*pDbgInfo,false,false);*/
    }

    return true;
}

bool Resolver::solve(ostream * pDbgInfo, bool bStatInfo, int maxResults) {

	int resultNum=0;

	this->pDbgInfo = pDbgInfo;

	bool finished=false;

    if (pDbgInfo)
        FillSteps.printInfo (*pDbgInfo);

    bool need_revert=false;
    bool reverted=false;
    bool done=false;

 //   FillStep* currentStep = NULL;//FillSteps.getBestStep(done);


	while (!finished)
	{
		// Find the best fill step to go

	    if (!need_revert && !reverted)
	    {
            FillStep * currentStep = FillSteps.getBestStep(done);

            if (done) {
                cout << "Result #" << ++resultNum << endl;
                bd.print(cout);//,false,false);

                if (maxResults>0 && resultNum>=maxResults) {
                    cout << "Not all results showed..." << endl;
                    break; //finished
                }

                need_revert=true;
            } else if (currentStep) {
              currentStep->first();
            } else {
               need_revert=true;
            }
	    } else if (reverted)
	    {
            if (FillSteps.getCurrentStep()->next())
            {
                reverted=false;
                need_revert = false;
            } else {
                reverted=false;
                need_revert=true;
            }

	    } else if (need_revert)
	    {
            // need_reverse
            if (!solve_stack.empty()) {

                /*
                if (pDbgInfo) {
                    *pDbgInfo << "Stack top before moving" <<endl;
                    solve_stack.top().bd_reverse.print(*pDbgInfo,false,false);
                }*/

//                  FillStepWithReverse stepRev = std::move(solve_stack.top()); //* pStep;

                FillStepRev_Ptr pStep = solve_stack.top();

                /*
                if (pDbgInfo) {
                    *pDbgInfo << "stepRev after moving" <<endl;
                    stepRev.bd_reverse.print(*pDbgInfo,false,false);
                    *pDbgInfo << "Stack top after moving" <<endl;
                    solve_stack.top().bd_reverse.print(*pDbgInfo,false,false);
                }*/

                solve_stack.pop();
                cPop++;


#ifdef RESOLVER_FAST_REVERSE_

                //currentStep = &stepRev.step;
//                this->bd = pStep->bd_reverse;
                this->bd = std::move (pStep->bd_reverse);
#ifdef RESOLVER_FAST_REVERSE_FILLSTEPS_
                this->FillSteps = std::move (pStep->FillSteps_reverse);
//                this->FillSteps = pStep->FillSteps_reverse;
#endif

                FillStep * currentStep = this->FillSteps.getCurrentStep();

#else

                currentStep->revertFill();
#endif

                //(*this->bd) = stepRev.bd_reverse;
                //(*this->bd) = std::move(stepRev.bd_reverse); // pStep->bd_reverse;

#ifndef RESOLVER_STL_
                delete pStep;
#endif

                if (pDbgInfo) {
                    (*pDbgInfo) << "Reverted:";
                    currentStep->print(*pDbgInfo);
                    bd.print(*pDbgInfo);//,false,false);

                    (*pDbgInfo) << "Reverted fill steps" << endl;
                    FillSteps.printInfo(*pDbgInfo);
                }



                reverted=true;
            } else break;
        }; // if (need_reverse)

	    if (!need_revert) {
            bool r= fillStep();
                //this step leads further invalid

            if (pDbgInfo && bStatInfo)
                FillSteps.printInfo (*pDbgInfo);

            if (!r)
            {
                if (pDbgInfo)
                    *pDbgInfo << "Invalid, need reverse" <<endl;
                need_revert = true;
            }
	    }
	}

	cout << "#Results: " << resultNum << endl;

	cout <<"Pushed :" << cPush << "Poped:" << cPop;

	return (resultNum>0);
}


/*void Resolver::printStatInfo (ostream & os, bool cand, bool area)
{
    if (cand) {
        os << "----- CAND ----" << endl;
        for (NUM_T y=1; y<=9; y++) {
            for (NUM_T x=1;x<=9;x++)
            {
                os<<x<<"-"<<y<<" ";
                candList[x][y].print(os);
            }
            os<<endl;
        }
    }

    if (area) {
        os << "---- AREAS ----" << endl;
        for (NUM_T i=0; i<27; i++) {
            areas[i].print(os);
            os<< "---" << endl;
        }
    }
}*/
