/*
 * Area.h
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#ifndef AREA_H_
#define AREA_H_

#include <iostream>
#include <array>
#include <functional>
#include "NumList.h"

enum AreaType {ROW, COL, SQR};

const int NUM_AREAS= 3 * 9;

class Board;

class Area {
public:
    Area():typ(ROW),anum(0){};
	Area(AreaType typ, NUM_T anum) : typ(typ), anum(anum) {};

	Area(AreaType typ, NUM_T x, NUM_T y) : typ(typ) {
	    switch (typ) {
	    case ROW: anum=y;break;
	    case COL: anum=x;break;
	    case SQR:
	        NUM_T xx=(x-1)/3;  //0,1,2
	        NUM_T yy=(y-1)/3;

	        anum=yy*3+xx+1; //0-8
	        break;
	    }
	}

	Area(int id) {
	    int tmp = id / 9;
	    switch (tmp) {
	    case 0: typ=ROW; break;
	    case 1: typ=COL; break;
	    case 2: typ=SQR; break;
	    //default: throw();
	    }

	    anum = id % 9 + 1;
	}

	static int getRowAreaID(NUM_T y) {
	    return y-1;
	}

	static int getColAreaID(NUM_T x) {
	    return 9 + x - 1;
	}

	static int getSqrAreaID(NUM_T x, NUM_T y) {

        NUM_T xx=(x-1)/3;  //0,1,2
        NUM_T yy=(y-1)/3;

        return 18+yy*3+xx;
    }

	static bool forEachThreeAreas(NUM_T x, NUM_T y, std::function <bool(const Area &a)> f )
	        //void (*f) (const Area & a))
	{
	    if (!f (Area(ROW,y))) return false;

	    if (!f (Area (COL,x))) return false;

	    if (!f (Area (SQR,x,y))) return false;

	    return true;
	}

	static void getThreeAreas(NUM_T x, NUM_T y, Area ars[])
	{
	    ars[0]=Area(ROW,y);
	    ars[1]=Area(COL,x);
	    ars[2]=Area(SQR,x,y);
	}


//	NumList* getMissingNumList ();
//	bool isNumInArea (NUM_T n);
//	void addNumInArea (NUM_T n);
//	void init (Board *bd,AreaType typ, NUM_T anum);
//	NumList* getNumPosList (NUM_T n);
	void getPos (NUM_T i, NUM_T &x, NUM_T &y)
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

	void getPosIdx (NUM_T x, NUM_T y, NUM_T & i) const
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

	int  getID() const
	{
	    return Area::getID(typ,anum);
	}

//	void print(ostream &os);

	static int getID(AreaType typ, NUM_T anum)
	{
	    int tmp;

        switch (typ) {
        case ROW: tmp=0; break;
        case COL: tmp=1; break;
        case SQR: tmp=2; break;
       // default: throw();
        }

        return tmp * 9 + anum-1;
	}

	void print (ostream& os) const {
	    os << "Area Type:" << typ << "  Area Num:" << anum;
	}

private:
//	Board * bd;

	AreaType typ;
    NUM_T anum;

#ifndef AREA_STL_

	NumList numPosList[10];

#else
//	std::array <NumList,10> numPosList;
#endif
};

#endif /* AREA_H_ */
