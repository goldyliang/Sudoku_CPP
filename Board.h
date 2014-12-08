/*
 * Board.h
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <fstream>
#include "NumList.h"


using std::ifstream;

class Area;

class Board
{
public:
	Board();
	~Board();
	bool initBoard(istream &f);

	bool fill (int x, int y, int n);
	bool fillable (int x, int y, int n);
	bool erase (int x, int y);
	int  get (int x, int y);
	NumList * getFillableList (int x, int y);

	Area * getRowArea(int y);
	Area * getColArea(int x);
	Area * getSqrArea(int x, int y);
	void   getThreeAreas(int x, int y, Area* ars[]);

	void   print(ostream & os, bool cand, bool area);

private:
	void updateFillable(int x, int y, int n);
	void markUnFillable(int x, int y, int n);
	int bd[10][10];
	NumList candList[10][10];
	Area* areas[3*9];
	    // 0-8: rows 1-9, 9-17: cols 1-9, 18-26: sqr 1-9
};

istream &operator >> (istream &is, Board &bd);

#endif /* BOARD_H_ */
