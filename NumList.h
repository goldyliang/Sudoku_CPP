/*
 * NumList.h
 *
 *  Created on: 2014Äê6ÔÂ19ÈÕ
 *      Author: Liang
 */

#ifndef NUMLIST_H_
#define NUMLIST_H_

#include <iostream>

using namespace std;

class NumList {
public:
	NumList();

	void makeFullList();
	void add(int n);
	void remove (int n);
	bool in (int n);
	int  numCount ();

	int getFirst();
	int getNext (int n);
	void print(ostream & os);
private:
	int cnt;
	bool b[10];
};

#endif /* NUMLIST_H_ */
