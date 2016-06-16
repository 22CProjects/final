/*	Anna Houk, Kiera Nguyen, Michael Phan*/
/* Specification and implementation of StackLinkedList ADT (derived from SinglyLinkedList) */
#pragma once

#include "SinglyLinkedList.h"
#include "Node.h"

template <class DataType>
class StackLinkedList : protected SinglyLinkedList<DataType>
{
public:
	/* DEFAULT CONSTRUCTOR */
	StackLinkedList() : SinglyLinkedList<DataType>() {}


	/* Definition of push
	- It adds newData to the list in a stack order
	- Parameter: a DataType variable to be added
	- Return: none
	*/
	void push(DataType newData) { addTop(newData); }

	/* Definition of pop
	- It deletes the last Node in the list (last in first out)
	- Parameter: none
	- Return: none
	*/
	void pop() 
	{
		DataType d = headNode.get_Front()->get_data();
		remove(d);
	}

	DataType peek(){
		return headNode.get_Front()->get_data();
	}

	/* Definition of isEmpty
	- It checks if the list is empty
	- Parameter: none
	- Return: a boolean true for empty list and false for having at least a node in the list
	*/
	bool isEmpty() 
	{
		if (headNode.get_nodeCounter() == 0) return true;
		else return false;
	}

	/* Definition of isEmpty
	- It checks if the list is empty
	- Parameter: none
	- Return: a boolean true for empty list and false for having at least a node in the list
	*/
	void emptyStack()	{	emptyList();	}

	/* Definition of countNodes (override)
	- It counts the total number of Nodes in the list by calling function getNodeCounter() from Head.h
	- Parameter: none
	- Return: an int (number of nodes)
	*/
	int countNodes() {	return headNode.get_nodeCounter();	}

	/*
	Definition of overladed operator<<
	- prints contents of the stack
	- Parameter: none
	- Return: void
	*/
	template<class DataType> friend ostream& operator<<(ostream&, const StackLinkedList<DataType>&);
};



template <class DataType>
ostream& operator<<(ostream& s, const StackLinkedList<DataType>& stack)
{
	Node<DataType>* temp = stack.headNode.get_Front();

	while (temp != nullptr)
	{
		s << "\t\t" << temp->get_data() << endl;
		temp = temp->get_next();
	}
	return s;
}






