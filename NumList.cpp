/*
 * NumList.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#include "NumList.h"
#include <iostream>

using std::cout;
using std::cerr;

#ifndef NUMLIST_STL_

NumList::NumList() {
	// TODO Auto-generated constructor stub
	cnt=0;
	for (NUM_T n=1;n<=9;n++)
		b[n]=false;
}


NUM_T NumList::getFirst()
{
	for (NUM_T n=1;n<=9;n++)
		if (b[n])
			return n;
	return 0;
}

NUM_T NumList::getNext (NUM_T n)
{
	for (NUM_T nn=n+1;nn<=9;nn++)
		if (b[nn])
			return nn;
	return 0;
}

void NumList::makeFullList()
{
	cnt=9;
	for (NUM_T n=1;n<=9;n++)
		b[n]=true;
}

void NumList::print(ostream & os)
{
//	if (os==NULL) os=(&cout);

	NUM_T c=0;
	for (NUM_T n=1;n<=9;n++) {
		if (b[n]) {
			os << n;
			c ++;
		}
	}
	for (;c<=9;c++)
		os << " ";
}

#else // NUMLIST_STL_ defined

NumList::NumList() : cnt(0) {
    // bitSet b shall be default initialized to all zero
}



NUM_T NumList::getFirst()
{
    return b._Find_first();
//    for (NUM_T n=1;n<=9;n++)
//        if (b[n])
//            return n;
//    return 0;
}

NUM_T NumList::getNext (NUM_T n)
{
    for (NUM_T nn=n+1;nn<=9;nn++)
        if (b[nn])
            return nn;
    return 0;
}

void NumList::makeFullList()
{
    cnt=9;
    for (NUM_T n=1;n<=9;n++)
        b[n]=true;
}

void NumList::print(ostream & os)
{
//  if (os==NULL) os=(&cout);

    NUM_T c=0;
    for (NUM_T n=1;n<=9;n++) {
        if (b[n]) {
            os << n;
            c ++;
        }
    }
    for (;c<=9;c++)
        os << " ";
}

#endif // NumList_STL

