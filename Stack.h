/*
 * stack.h
 *
 *  Created on: 2014Äê5ÔÂ28ÈÕ
 *      Author: Liang
 */

#ifndef STACK_H_
#define STACK_H_

#include <iostream>

template <typename DataType>
class Stack
{
	public:
		void push (const DataType & dt);
		bool pop(DataType& dt);
		Stack ();
		~Stack ();

	private:
		struct Node
		{
			DataType d;
			Node * next;
		};
		Node * top, * bottom;
		int node_cnt;

};



template <typename DataType>
Stack<DataType>::Stack()
{
	//std::clog << "Stack constructed.\n";
	top=bottom=NULL;
	node_cnt=0;
}

template <typename DataType>
Stack<DataType>::~Stack()
{
	Node * pt;

	pt=bottom;

	while (pt) {
		Node * pt_tmp=pt;
		pt = pt->next;
		delete pt_tmp;
		//std::clog << "Node deleted.]n";
	}

	//std::clog << "Stack destructed.";
}

template <typename DataType>
void Stack<DataType>::push (const DataType & dt)
{
	Node * nw = new Node;
	nw->d = dt;
	//nw->next = NULL;

	if (top) {
		nw->next = top;
		top = nw;
	} else {
		top = bottom = nw;
		nw->next = NULL;
	}

	node_cnt ++;

	//std::clog << "Stack pushed :" << node_cnt << "\n";
}

template <typename DataType>
bool Stack<DataType>::pop (DataType & dt)
{
	if (top) {
		dt=top-> d;
		Node * nd = top;
		top = top -> next;
		delete nd;
		if (!top) bottom=NULL;

		node_cnt --;
	//	std::clog << "Stack popped." << node_cnt << "\n";

		return true;
	} else return false;
}

#endif /* STACK_H_ */
