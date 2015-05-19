/*
 * Board.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */
//#include <cstdio>
#include "Board.h"
//#include "Area.h"
#include <iostream>
#include <exception>

using std::cerr;
using std::endl;
using std::cout;

Board::Board()
{

    bd.resize(10);

//    candList.resize(10);
//    for (NUM_T i=1;i<=9;i++)
//        candList[i].resize(10);

//    bd.resize(10);
//    for (NUM_T i=1;i<=9;i++)
//        bd[i].resize(10);

	for (NUM_T x=1;x<=9;x++)
		for (NUM_T y=1;y<=9;y++)
		{
			bd[x][y]=0;
//			candList[x][y].makeFullList();
		}

//	areas.resize(27);

/*	NUM_T i=0;
	for (NUM_T y=1;y<=9;y++)
		areas[i++].init(this,ROW,y);

	for (NUM_T x=1;x<=9;x++)
		areas[i++].init(this,COL,x);

	for (NUM_T anum=1; anum<=9; anum++)
		areas[i++].init(this,SQR,anum); */
}

/*Board::Board( Board& brd) : bd(brd.bd)
{
}


Board::Board( Board&& brd) noexcept : bd(std::move(brd.bd))
{
}

Board & Board::operator = (const Board & brd)
{
    this->bd = brd.bd;
    return *this;
}


Board & Board::operator = (Board && brd) noexcept
{
    this->bd = std::move (brd.bd);
    return *this;
}

*/

bool Board::initBoard(istream &f)
{
//	try {
		for (NUM_T y=1;y<=9;y++)
			for (NUM_T x=1;x<=9;x++)
			{
				char c;
				f >> c;
				NUM_T n = c-'0';
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

bool Board::fill (NUM_T x, NUM_T y, NUM_T n)
{
	if (x<1 || x>9 || y<1 || y>9 || n<1 || n>9) {
		cerr << "Fill " << x << "," << y << "," << n <<endl;
		return false;
	}

//	if (!candList[x][y].in(n)) return false;


	bd[x][y]=n;

/*
	//Clear candList[x][y]
	candList[x][y].clear();


    // to improve: use Lumda expression
    Area * ars[3];
    getThreeAreas(x,y,ars);


    for (NUM_T ari=0;ari<3;ari++)
    {
        Area * ar=ars[ari];

        for (NUM_T i=1;i<=9;i++)
        {
            NUM_T tx,ty;
            ar->getPos(i,tx,ty);
            candList[tx][ty].remove(n);


        }

        ar->getNumPosList(n)->clear();

        NUM_T i;
        ar->getPosIdx(x,y,i);

        for (NUM_T nn=1;nn<=9;nn++)
            ar->getNumPosList(nn)->remove(i);


    }*/


/*	for (NUM_T nn=1;nn<=9;nn++)
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
	}*/
	return true;
}

bool Board::fillable(NUM_T x, NUM_T y, NUM_T n)
{
//	if (!candList[x][y].in(n))
    if (bd[x][y])
   	    return false;
	else
		return true;
}

bool Board::erase (NUM_T x, NUM_T y)
{
	if (bd[x][y]==0) return false;

/*	candList[x][y].add(bd[x][y]);

	NUM_T n=bd[x][y];*/

	bd[x][y]=0;

/*	for (NUM_T nn=1;nn<=9;nn++)
		updateFillable(x,y,nn);

	Area * ars[3];
	getThreeAreas(x,y,ars);

	for (NUM_T ari=0;ari<3;ari++)
	{
		Area * ar=ars[ari];
		for (NUM_T i=1;i<=9;i++)
		{
			NUM_T tx,ty;
			ar->getPos(i,tx,ty);
			updateFillable(tx,ty,n);
		}
	}*/

	return true;

}

NUM_T Board::get (NUM_T x, NUM_T y)
{
	return bd[x][y];
}

/*NumList * Board::getFillableList (NUM_T x, NUM_T y)
{
//	return &(candList[x][y]);
}*/



/*void   Board::getThreeAreas(NUM_T x, NUM_T y, Area* ars[])
{
	ars[0]=getRowArea(y);
	ars[1]=getColArea(x);
	ars[2]=getSqrArea(x,y);
}
*/

void   Board::print(ostream & os) //, bool cand, bool area)
{
	os << (long int)&(bd[1][1])<<"---------" << endl;

/*	if (bd.size()!=10) {
	    os << "Invalid" <<endl;
	    return;
	} */

	try {
        for (NUM_T y=1;y<=9;y++) {
            for (NUM_T x=1;x<=9;x++)
                os << bd[x][y];
            os << endl;
        }
        os << endl;



//        os << "Add:" << &(bd[1][1]) << endl;
	} catch (exception &e)
	{
	    os << "Board invalid for print" << endl;
	}
}
