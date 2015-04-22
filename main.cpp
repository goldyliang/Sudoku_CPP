/*
 * main.cpp
 *
 *  Created on: 2014��6��19��
 *      Author: Liang
 */
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "Resolver.h"

using namespace std;

int main ()
{

//Test Board.cpp

	Board bd;
	ifstream fl;

	fl.open("bd.txt");
//	if (fl.is_open())
//	{
	//bd.initBoard (cin);
	//fl >> bd;
	if (!fl || !(fl >> bd)) {
		cout << "Error input!" << endl;
		exit (1);
	}
//	}

/* debug of Board.cpp */
/*	bd.print(true,true);

	bd.fill(5,6,1);
	bd.print(true,true);

	bd.erase(5,6);

	bd.print(true,true); */


	cout << "Initial State:" << endl;
	bd.print(cout,false,false);
	cout << endl;

	Resolver sol(&bd);

	sol.solve(NULL); //&std::cout);

	//bd.print(false,false);

}
