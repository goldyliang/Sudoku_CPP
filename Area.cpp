/*
 * Area.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#include "Area.h"
#include "Board.h"
#include <iostream>

using std::cout;
using std::endl;

void Area::init(Board *bd, AreaType typ, NUM_T anum) {

//	this->bd=bd;
	this->typ=typ;
	this->anum=anum;

	NUM_T x,y;

	for (NUM_T i=1;i<=9;i++)
	{
		getPos(i,x,y);
		for (NUM_T n=1;n<=9;n++)
			if (bd->fillable(x,y,n)) {
				numPosList[n].add(i);
			}
	}
}

NumList* Area::getNumPosList (NUM_T n)
{
	return &(numPosList[n]);
}

/*bool Area::isNumInArea (NUM_T n)
{
	for (NUM_T i=1;i<=9;i++)
	{
		NUM_T x,y;
		getPos(i,x,y);
		if (bd->get(x,y)==n) return true;
	}
	return false;
}*/


void Area::getPos (NUM_T i, NUM_T &x, NUM_T &y)
{
	switch (typ)
	{
	case ROW:
		x=i; y=anum; break;
	case COL:
		x=anum; y=i; break;
	case SQR:
		NUM_T x0= (anum-1) % 3 * 3 + 1;
		NUM_T y0 = (anum-1) / 3 * 3 + 1;
		x=x0 + (i-1) % 3;
		y=y0 + (i-1) / 3;
		break;
	}
}

void Area::getPosIdx (NUM_T x, NUM_T y, NUM_T & i)
{
	switch (typ)
	{
	case ROW:
		if (y==anum)
			i = x;
		else
			i = 0;
		break;
	case COL:
		if (x==anum)
			i = y;
		else
			i = 0;
		break;
	case SQR:
		NUM_T x0= (anum-1) % 3 * 3 + 1;
		NUM_T y0 = (anum-1) / 3 * 3 + 1;
		if (x>=x0 && x<x0+3 && y>=y0 && y<y0+3)
			i = (y-y0)*3 + x-x0 + 1;
		else
			i=0;
		break;
	}
}

void Area::print(ostream & os)
{
//	if (!os) os=(&cout);

	switch (typ)
	{
	case ROW: cout << "R"; break;
	case COL: cout << "C"; break;
	case SQR: cout << "Q"; break;
	}

	os << anum << ":" << endl;

	for (NUM_T n=1;n<=9;n++)
	{
		os<<n<<":";
		numPosList[n].print(os);
		os<<endl;
	}
}

