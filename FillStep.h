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

using namespace std;

class FillStep {
public:
	FillStep();
	virtual ~FillStep();
	virtual NUM_T  candCount()=0;
	virtual void first()=0;
	virtual bool next()=0;
	virtual void print(ostream &os);

	virtual bool solved()=0;
	void applyFill();
	void revertFill();
protected:
	bool m_solved;
	Board * bd;
	NUM_T x,y,n;
};

class NumCandStep:public FillStep {
public:
    NumCandStep (Board * bd, NUM_T x, NUM_T y) : bd(bd), x(x), y(y) {};
	void init (Board * bd, NUM_T x, NUM_T y);
	virtual NUM_T  candCount();
	virtual void first();
	virtual bool next();
	virtual void print(ostream & os);
	virtual bool solved();
};

class PosCandStep:public FillStep {
	public:
        PosCandStep (Board * bd, Area * ar, NUM_T n);
		void init (Board * bd, Area * ar, NUM_T n);
		virtual NUM_T  candCount();
		virtual void first();
		virtual bool next();
		virtual void print(ostream & os);
		virtual bool solved();
	private:
		Area * ar;
		NumList * numList;

		NUM_T curPos;

};


#endif /* FILLSTEP_H_ */
