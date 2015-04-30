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
#include "NumList.h"

enum AreaType {ROW, COL, SQR};

class Board;

class Area {
public:
//	Area(Board *bd, AreaType typ, NUM_T anum);

//	NumList* getMissingNumList ();
//	bool isNumInArea (NUM_T n);
//	void addNumInArea (NUM_T n);
	void init (Board *bd,AreaType typ, NUM_T anum);
	NumList* getNumPosList (NUM_T n);
	void getPos (NUM_T i, NUM_T &x, NUM_T &y);
	void getPosIdx (NUM_T x, NUM_T y, NUM_T & i);
	void print(ostream &os);

private:
//	Board * bd;

	AreaType typ;
    NUM_T anum;

#ifndef AREA_STL_

	NumList numPosList[10];

#else
	std::array <NumList,10> numPosList;
#endif
};

#endif /* AREA_H_ */
