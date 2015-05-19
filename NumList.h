/*
 * NumList.h
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#ifndef NUMLIST_H_
#define NUMLIST_H_

#include <iostream>
#include <bitset>
#include "common.h"

using namespace std;


class NumList {
public:
	NumList();

	void makeFullList();

	void add(NUM_T n)  INLINE_CONF
	{
	    if (!b[n]) cnt++;
	    b[n]=true;
	}

	void remove (NUM_T n) INLINE_CONF
    {
	    if (b[n]) cnt--;
	    b[n]=false;
	}


	bool in (NUM_T n) const INLINE_CONF
    {
	    return b[n];
	}

	NUM_T  numCount () const INLINE_CONF
    {
	    return cnt;
	}

	void clear() INLINE_CONF
	{
	    b.reset();
	    cnt=0;
	}

	NUM_T getFirst() const;
	NUM_T getNext (NUM_T n) const;
	void print(ostream & os) const;
private:

#ifndef NUMLIST_STL_

	NUM_T cnt;
	bool b[10];

#else   // NUMLIST_STL_ defined
	NUM_T cnt; //keep tracking the counter outside of std::bitset for performance consideration
	std::bitset<10> b;
#endif  // NUMLIST_STL_


};

#endif /* NUMLIST_H_ */
