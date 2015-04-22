/*
 * Area.h
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#ifndef AREA_H_
#define AREA_H_

#include <iostream>
#include "NumList.h"

enum AreaType {ROW, COL, SQR};

class Board;

class Area {
public:
//	Area(Board *bd, AreaType typ, int anum);

//	NumList* getMissingNumList ();
//	bool isNumInArea (int n);
//	void addNumInArea (int n);
	void init (Board *bd,AreaType typ, int anum);
	NumList* getNumPosList (int n);
	void getPos (int i, int &x, int &y);
	void getPosIdx (int x, int y, int & i);
	void print(ostream &os);

private:
//	Board * bd;
	AreaType typ;
	int anum;
	NumList numPosList[10];
};

#endif /* AREA_H_ */
