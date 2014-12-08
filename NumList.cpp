/*
 * NumList.cpp
 *
 *  Created on: 2014Äê6ÔÂ19ÈÕ
 *      Author: Liang
 */

#include "NumList.h"
#include <iostream>

using std::cout;
using std::cerr;

NumList::NumList() {
	// TODO Auto-generated constructor stub
	cnt=0;
	for (int n=1;n<=9;n++)
		b[n]=false;
}

void NumList::add(int n)
{
	if (!b[n]) cnt++;
	b[n]=true;
}

void NumList::remove (int n)
{
	if (b[n]) cnt--;
	b[n]=false;
}

bool NumList::in (int n)
{
	return b[n];
}

int  NumList::numCount ()
{
	return cnt;
}

int NumList::getFirst()
{
	for (int n=1;n<=9;n++)
		if (b[n])
			return n;
	return 0;
}

int NumList::getNext (int n)
{
	for (int nn=n+1;nn<=9;nn++)
		if (b[nn])
			return nn;
	return 0;
}

void NumList::makeFullList()
{
	cnt=9;
	for (int n=1;n<=9;n++)
		b[n]=true;
}

void NumList::print(ostream & os)
{
//	if (os==NULL) os=(&cout);

	int c=0;
	for (int n=1;n<=9;n++) {
		if (b[n]) {
			os << n;
			c ++;
		}
	}
	for (;c<=9;c++)
		os << " ";
}
