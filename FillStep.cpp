/*
 * FillStep.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#include "FillStep.h"
#include "Board.h"


using std::cout;
using std::endl;

FillStep::FillStep()
{
	m_solved=false;
	bd=NULL;
	x=y=n=0;
}

FillStep::~FillStep()
{
	return;
}



void FillStep::applyFill()
{
	bd->fill(x,y,n);
}

void FillStep::revertFill()
{
	bd->erase(x,y);
}

void FillStep::print(ostream &os)
{
//	if (!os) os=(&cout);
	os << "(" << x << "," << y << ")-" << n << "---";
}

void NumCandStep::init (Board * bd, NUM_T x, NUM_T y)
{
	this->bd = bd;
	this->x=x;
	this->y=y;
}

NUM_T NumCandStep::candCount()
{
	return this->bd->getFillableList(x,y)->numCount();
}

void NumCandStep::first()
{
	this->n = bd->getFillableList(x,y)->getFirst();
}

bool NumCandStep::next()
{
	n = bd->getFillableList(x,y)->getNext(n);
	return n;
}

void NumCandStep::print(ostream &os)
{
//	if (!os) os=(&cout);

	FillStep::print(os);
	bd->getFillableList(x,y)->print(os);
	os<<endl;
}

bool NumCandStep::solved()
{
	if (bd->get(x,y)==0)
		return false;
	else
		return true;
}

void PosCandStep::PosCandStep (Board * bd, Area * ar, NUM_T n)
{
    init (bd,ar,n);
}

void PosCandStep::init (Board * bd, Area * ar, NUM_T n)
{
	this->bd=bd;
	this->ar=ar;
	this->n=n;
	this->numList = ar->getNumPosList(n);
}

NUM_T PosCandStep::candCount()
{
	return numList->numCount();
}

void PosCandStep::first()
{
	curPos=numList->getFirst();
	ar->getPos(curPos,x,y);
}

bool PosCandStep::next()
{
	curPos=numList->getNext(curPos);
	if (curPos>0)
		ar->getPos(curPos,x,y);
	return curPos;

}

void PosCandStep::print(ostream &os)
{
//	if (!os) os =(&cout);

	FillStep::print(os);
	os << endl;
	ar->print(os);
}

bool PosCandStep::solved()
{
	return ar->getNumPosList(n)->numCount()==0;
}
