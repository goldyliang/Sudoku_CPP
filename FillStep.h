/*
 * FillStep.h
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#ifndef FILLSTEP_H_
#define FILLSTEP_H_

#include "Area.h"
#include <iostream>
#include <vector>
#include <memory>
#include <array>
#include <list>

using namespace std;

class Resolver;
class FillStep;

typedef list<FillStep*>::iterator stepIterator;


class FillStep {
public:
	//FillStep() : bd(NULL), m_solved(false) {};
//	FillStep(Board * bd, Resolver * rs, NUM_T x, NUM_T y, NUM_T n) :
//	    bd(bd), rs(rs), m_solved(false), x(x), y(y), n(n), i(0) {};
	void init (NUM_T x, NUM_T y, NUM_T n);
	virtual ~FillStep();
	virtual NUM_T  candCount() const =0;
	virtual void first()=0;
	virtual bool next()=0;
	virtual bool isLast();
	virtual void print(ostream &os, bool breif=false) const;

//	virtual bool solved() const =0;

	//remove one candidate. return false if none candidate available
	//move the FillStep to proper location in FillStepList
	virtual bool removeCand (NUM_T cand)=0;
	//virtual bool markSolved() =0; //
	virtual	void applyFill(Board &bd);

	void revertFill(Board & bd);
protected:
	//Board * bd;
	//Resolver * rs;
    bool solved;
    NUM_T x,y,n;
    NUM_T i; //current number of try (from 1)
    stepIterator it; // iterator in the StepList of myself

    friend class Resolver;
    friend class FillStepList;
};

typedef shared_ptr<FillStep> FillStep_Ptr;


class NumCandStep:public FillStep {
    public:

 //       NumCandStep ();//Board * bd, Resolver * rs, NUM_T x, NUM_T y);
        void init (NUM_T x, NUM_T y);
        virtual NUM_T  candCount() const;
        virtual void first();
        virtual bool next();
        virtual void print(ostream & os, bool breif=false) const;
      //  virtual bool solved() const;
 //       static void markUnFillable (NUM_T x, NUM_T y, NUM_T n);
        virtual bool removeCand (NUM_T cand);
 //       virtual bool markSolved() ; //

    protected:
        NumList numCands;
 //       static ARRAY_9_9_T<NumCandStep*> p_NumCandSteps;

        friend class FillStepList;

};


class PosCandStep:public FillStep {
	public:
 //       PosCandStep ();//Board * bd, Resolver * rs, Area ar, NUM_T n);
        void init (Area ar, NUM_T n);
		virtual NUM_T  candCount() const;
		virtual void first();
		virtual bool next();
		virtual void print(ostream & os, bool breif=false) const;
		//virtual bool solved() const;
 //       static void markUnFillable (NUM_T x, NUM_T y, NUM_T n);

        virtual bool removeCand (NUM_T cand);
 //       virtual bool markSolved();

	private:
		Area ar;
//		NumList * numList;

	    NumList posCands;

		NUM_T curPos;
//		static array< array<PosCandStep*,10> , NUM_AREAS> p_PosCandSteps;

        friend class FillStepList;


};


class FillStepList
{
public:

    FillStepList ();
    FillStepList (FillStepList& ls); // copy constructor

    FillStepList& operator = (FillStepList && ls) noexcept;
    FillStepList &operator = (FillStepList &ls);



    FillStep* getBestStep(bool & done);

    void updatePos (FillStep_Ptr st);

    bool markSolved (NUM_T x, NUM_T y, NUM_T n);
    bool markUnFillable (NUM_T x, NUM_T y, NUM_T n);
    bool updateSteps (NUM_T x, NUM_T y, NUM_T n); // return false if a step becomes not applicable

    void printInfo (ostream & os);

    FillStep * getCurrentStep() {return pStep;};


private:
//    Board * bd;
 //   Resolver * rs;

    // Todo: make this copiable and movable
    typedef list <FillStep*> FillStepLinkedList;

    vector <FillStepLinkedList> m_list; //0 for solved
   // vector < FillStep * > m_list;


    stepIterator add (FillStep * st);

    bool removeCandAndMove (FillStep * st, NUM_T cand); // return false if no candidates
    void markSolvedAndMove (FillStep * st);

 //   stepIterator move (stepIterator , NUM_T prev_candCnt); //return the new iterator of the element


 /*   struct NumCandStepWIterator
    {
        NumCandStep st;
        stepIterator it;
    } ;

    struct PosCandStepWIterator
    {
        PosCandStep st;
        stepIterator it;
    } ;*/

    vector < array <NumCandStep, 10> > numCandSteps;
    vector < array<PosCandStep,10>> posCandSteps;

    FillStep * pStep;

};

#endif /* FILLSTEP_H_ */
