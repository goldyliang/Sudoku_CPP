/*
 * Board.cpp
 *
 *  Created on: 2014Äê6ÔÂ19ÈÕ
 *      Author: Liang
 */
//#include <cstdio>
#include "Board.h"
#include "Area.h"
#include <iostream>

using std::cerr;
using std::endl;
using std::cout;

Board::Board()
{
	for (int x=1;x<=9;x++)
		for (int y=1;y<=9;y++)
		{
			bd[x][y]=0;
			candList[x][y].makeFullList();
		}

	int i=0;
	for (int y=1;y<=9;y++)
		areas[i++]=new Area(this,ROW,y);

	for (int x=1;x<=9;x++)
		areas[i++]=new Area(this,COL,x);

	for (int anum=1; anum<=9; anum++)
		areas[i++]=new Area(this,SQR,anum);
}

Board::~Board()
{
	for (int i=0;i<27;i++)
		if (areas[i])
			delete areas[i];
}


bool Board::initBoard(istream &f)
{
//	try {
		for (int y=1;y<=9;y++)
			for (int x=1;x<=9;x++)
			{
				char c;
				f >> c;
				int n = c-'0';
				if (n>0) {
					if (!fill(x,y,n)) return false;
				}
			}
//	} catch ()
//	{
//		return false;
//	}
	return true;
}

istream &operator >> (istream &is, Board &bd)
{
	if (!bd.initBoard(is))
		is.setstate(is.rdstate() & is.failbit);

	return is;
}

void Board::markUnFillable(int x, int y, int n)
{
	candList[x][y].remove(n);

	Area * ars[3];
	getThreeAreas(x,y,ars);

	for (int ari=0;ari<3;ari++)
	{
		int i;
		ars[ari]->getPosIdx(x,y,i);
		ars[ari]->getNumPosList(n)->remove(i);
	}
}

void Board::updateFillable(int x, int y, int n)
{
	Area * ars[3];
	getThreeAreas(x,y,ars);

	bool fillable=true;

	if (bd[x][y]>0)
		fillable=false;
	else
		for (int ari=0;ari<3;ari++)
		{
			Area * ar=ars[ari];
			for (int i=1;i<=9;i++)
			{
				int tx,ty;
				ar->getPos(i,tx,ty);
				if (bd[tx][ty]==n) {
					fillable=false;
					break;
				}
			}
		}

	if (fillable) {
		candList[x][y].add(n);

		for (int ari=0;ari<3;ari++)
		{
			Area * ar=ars[ari];
			int i;
			ar->getPosIdx(x,y,i);
			ar->getNumPosList(n)->add(i);
		}
	}
}

bool Board::fill (int x, int y, int n)
{
	if (x<1 || x>9 || y<1 || y>9 || n<1 || n>9) {
		cerr << "Fill " << x << "," << y << "," << n <<endl;
		return false;
	}

	if (!candList[x][y].in(n)) return false;


	bd[x][y]=n;

	for (int nn=1;nn<=9;nn++)
		markUnFillable(x,y,nn); //candList[x][y].remove(n);

	Area * ars[3];
	getThreeAreas(x,y,ars);

	for (int ari=0;ari<3;ari++)
	{
		Area * ar=ars[ari];
		for (int i=1;i<=9;i++)
		{
			int tx,ty;
			ar->getPos(i,tx,ty);
			markUnFillable(tx,ty,n);
		}
	}
	return true;
}

bool Board::fillable(int x, int y, int n)
{
	if (!candList[x][y].in(n))
   	    return false;
	else
		return true;
}

bool Board::erase (int x, int y)
{
	if (bd[x][y]==0) return false;

	candList[x][y].add(bd[x][y]);

	int n=bd[x][y];

	bd[x][y]=0;

	for (int nn=1;nn<=9;nn++)
		updateFillable(x,y,nn);

	Area * ars[3];
	getThreeAreas(x,y,ars);

	for (int ari=0;ari<3;ari++)
	{
		Area * ar=ars[ari];
		for (int i=1;i<=9;i++)
		{
			int tx,ty;
			ar->getPos(i,tx,ty);
			updateFillable(tx,ty,n);
		}
	}

	return true;

}

int Board::get (int x, int y)
{
	return bd[x][y];
}

NumList * Board::getFillableList (int x, int y)
{
	return &(candList[x][y]);
}

Area * Board::getRowArea(int y)
{
	return areas[y-1];
}

Area * Board::getColArea(int x)
{
	return areas[x+8];
}

Area * Board::getSqrArea(int x, int y)
{
	int xx=(x-1)/3;  //0,1,2
	int yy=(y-1)/3;

	return areas[18+yy*3+xx];
}

void   Board::getThreeAreas(int x, int y, Area* ars[])
{
	ars[0]=getRowArea(y);
	ars[1]=getColArea(x);
	ars[2]=getSqrArea(x,y);
}

void   Board::print(ostream & os, bool cand, bool area)
{
	os << "---------" << endl;
	for (int y=1;y<=9;y++) {
		for (int x=1;x<=9;x++)
			os << bd[x][y];
		os << endl;
	}
	os << endl;

	if (cand) {
		os << "----- CAND ----" << endl;
		for (int y=1; y<=9; y++) {
			for (int x=1;x<=9;x++)
			{
				os<<x<<"-"<<y<<" ";
				candList[x][y].print(os);
			}
			os<<endl;
		}
	}

	if (area) {
		os << "---- AREAS ----" << endl;
		for (int i=0; i<27; i++) {
			areas[i]->print(os);
			os<< "---" << endl;
		}
	}
}
