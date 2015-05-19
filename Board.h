/*
 * Board.h
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <fstream>
#include <array>
#include <vector>
#include "NumList.h"
#include "Area.h"

using std::ifstream;

#ifdef BOARD_STL_

//template <class etyp_>
//using ARRAY_9_9_T = std::array <std::array<etyp_,10>,10>;

//#define ARRAY_9_9_T( _etyp_)  std::array < std::array<_etyp_, 10> , 10>
//#define ARRAY_9_9_T( _etyp_)  std::vector < std::vector<_etyp_>>
#endif

class Board
{
public:
	Board();
//	Board (const Board & b) : bd(b.bd), candList(b.candList), areas(b.areas) {};
//	Board (Board && b) : bd(std::move(b.bd)), candList(std::move(b.candList)), areas(std::move(b.areas)) {};

/*	Board& operator = (const Board& other) {
	    bd = other.bd;
	    candList = other.candList;
	    areas = other.areas;
	    return *this;
	}*/

/*	Board (Board&brd);
	Board( Board&& brd) noexcept;
	Board & operator = (const Board & brd);
	Board & operator = (Board && brd) noexcept;*/
	bool initBoard(istream &f);

	bool fill (NUM_T x, NUM_T y, NUM_T n);
	bool fillable (NUM_T x, NUM_T y, NUM_T n);
	bool erase (NUM_T x, NUM_T y);
	NUM_T  get (NUM_T x, NUM_T y);
	//NumList * getFillableList (NUM_T x, NUM_T y);



	bool   valid();
	void   print(ostream & os);//, bool cand, bool area);

private:


#ifndef BOARD_STL_
	NUM_T bd[10][10];
	NumList candList[10][10];
	Area areas[3*9];
	    // 0-8: rows 1-9, 9-17: cols 1-9, 18-26: sqr 1-9
#else
	//TO be improve: it can be moved
	//ARRAY_9_9_T <NUM_T>  bd;
	vector < array <NUM_T, 10> > bd;

#endif

	friend class Resolver;


};

istream &operator >> (istream &is, Board &bd);

#endif /* BOARD_H_ */
