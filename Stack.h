/*
 * stack.h
 *
 *  Created on: 2014��5��28��
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
		DataType& top();
		void pop();
		bool empty();
		//bool pop(DataType& dt);
		Stack ();
		~Stack ();

	private:
		struct Node
		{
			DataType d;
			Node * next;
		};
		Node * n_top, * n_bottom;
		int node_cnt;

};



template <typename DataType>
Stack<DataType>::Stack()
{
	//std::clog << "Stack constructed.\n";
	n_top=n_bottom=NULL;
	node_cnt=0;
}

template <typename DataType>
Stack<DataType>::~Stack()
{
	Node * pt;

	pt=n_bottom;

	while (pt) {
		Node * pt_tmp=pt;
		pt = pt->next;
		delete pt_tmp;
		//std::clog << "Node deleted.]n";
	}

	//std::clog << "Stack destructed.";
}

template <typename DataType>
bool Stack<DataType>::empty()
{
    return n_top==NULL;
}

template <typename DataType>
void Stack<DataType>::push (const DataType & dt)
{
	Node * nw = new Node;
	nw->d = dt;
	//nw->next = NULL;

	if (n_top) {
		nw->next = n_top;
		n_top = nw;
	} else {
		n_top = n_bottom = nw;
		nw->next = NULL;
	}

	node_cnt ++;

	//std::clog << "Stack pushed :" << node_cnt << "\n";
}

template <typename DataType>
DataType& Stack<DataType>::top ()
{
    if (n_top) {
        return n_top->d;
    } else throw;
}

template <typename DataType>
void Stack<DataType>::pop ()
{
	if (n_top) {
		Node * nd = n_top;
		n_top = n_top -> next;
		delete nd;
		if (!n_top) n_bottom=NULL;

		node_cnt --;
	//	std::clog << "Stack popped." << node_cnt << "\n";
	}
}

#endif /* STACK_H_ */
