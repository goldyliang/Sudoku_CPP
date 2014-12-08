/*
 * FillStep.h
 *
 *  Created on: 2014Äê6ÔÂ19ÈÕ
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
	virtual int  candCount()=0;
	virtual void first()=0;
	virtual bool next()=0;
	virtual void print(ostream &os);

	virtual bool solved()=0;
	void applyFill();
	void revertFill();
protected:
	bool m_solved;
	Board * bd;
	int x,y,n;
};

class NumCandStep:public FillStep {
public:
	void init (Board * bd, int x, int y);
	virtual int  candCount();
	virtual void first();
	virtual bool next();
	virtual void print(ostream & os);
	virtual bool solved();
};

class PosCandStep:public FillStep {
	public:
		void init (Board * bd, Area * ar, int n);
		virtual int  candCount();
		virtual void first();
		virtual bool next();
		virtual void print(ostream & os);
		virtual bool solved();
	private:
		Area * ar;
		NumList * numList;

		int curPos;

};


#endif /* FILLSTEP_H_ */
