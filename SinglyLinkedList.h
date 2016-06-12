/* Specification and implementation of SinglyLinkedList*/
#pragma once

#include "Node.h"
#include "Head.h"
#include <iostream>
using namespace std;

template <class DataType>
class SinglyLinkedList
{
protected:
	Head<DataType> headNode;

public:
	/* DEFAULT CONSTRUCTOR */
	SinglyLinkedList();
	
	/* Destructor
		-deallocates memory of the nodes in the list
	*/
	~SinglyLinkedList();

	/* Definition of addTop
		- It adds newData to the front of thelist
		- Parameter: a DataType variable to be added
		- Return: none
	*/
	void addTop(DataType newData);

	/* Definition of addEnd
	- It adds newData to the end of the list
	- Parameter: a DataType variable to be added
	- Return: none
	*/
	void addEnd(DataType newData);

	/* Definition addAfter
	- It adds newNode after an existing node in the list
	- Parameter: 
	      + newData: the info being insterted into the list
	      + preData: the data to insert the newData after
	- Return: none
	*/
	void addAfter(DataType newData, DataType preData);

	/* Definition addToPos
	- It adds newNode to a specified position in the list
	- Parameters:
		  + newData: the info being insterted into the list
	      + pos: the position to insert the node in
	- Return: none
	*/
	void addToPos(DataType newData, int pos);

	/* Definition of deleteNode
		- It removes a Node from the list
		- Parameter: a Node variable to be deleted
		- Return: none
	*/
	void remove(DataType data2delete);

	/* Definition of find
		- It traverses through the list to find the Node
		- Parameter: a Node variable to be searched
		- Return: an int (for position of that Node in the list)
	*/
	int find(DataType data2find);

	/* Definition of emptyList
		- It removes all the Nodes in the list
		- Parameter: none
		- Return: none
	*/
	void emptyList();

	/*	Definition of countNodes
		- It counts the total number of Nodes in the list by calling function getNodeCounter() from Head.h
		- Parameter: none
		- Return: an int (number of nodes)
	*/
	virtual int countNodes();

	/*
		Definition of overloaded operator<<
		- prints contents of the list
		- Parameter: none
		- Return: void
	*/
	template<class DataType> friend ostream& operator<<(ostream&, const SinglyLinkedList<DataType>&);
	DataType* get_node_address(DataType data2find);

	DataType get_node_data(DataType data2find);
};



template <class DataType>
SinglyLinkedList<DataType>::SinglyLinkedList()
{
}//end default contructor

template <class DataType>
SinglyLinkedList<DataType>::~SinglyLinkedList()
{
	emptyList();
}//end deconstructor

template <class DataType>
void SinglyLinkedList<DataType>::addTop(DataType newData)
{
	Node<DataType>* newNode;
	newNode = new Node<DataType>(newData, headNode.get_Front());
	headNode.set_Front(newNode);
	if (newNode->get_next() == nullptr)headNode.set_Rear(newNode);

	++headNode;
}//end addTop

template <class DataType>
void SinglyLinkedList<DataType>::addEnd(DataType newData)
{
	Node<DataType>* newNode;
	Node<DataType>* temp_f = headNode.get_Front();

	
	if (countNodes() == 0)
	{
		newNode = new Node<DataType>(newData, headNode.get_Front());
		headNode.set_Front(newNode);
		headNode.set_Rear(newNode);

		++headNode;
	}
	else
	{
		newNode = new Node<DataType>(newData,nullptr);
		

		while (temp_f->get_next() != nullptr)
		{
			temp_f = temp_f->get_next();
		}
		temp_f->set_next(newNode);
		headNode.set_Rear(newNode);
		++headNode;
	}
	
}//end addEnd

template <class DataType>
void SinglyLinkedList<DataType>::addAfter(DataType newData, DataType preData)
{
	Node<DataType>* newNode;
	Node<DataType>* temp_f = headNode.get_Front();
	Node<DataType>* temp_b;

	if (find(preData) != -1)
	{
		while (temp_f->get_data() != preData)
		{
			temp_f = temp_f->get_next();
		}
		temp_b = temp_f;
		temp_f = temp_f->get_next();
		newNode = new Node<DataType>(newData, temp_f);
		temp_b->set_next(newNode);
		if (newNode->get_next() == nullptr)headNode.set_Rear(newNode);

		++headNode;
	}
	else
	{
		cout << preData << " is not in the List";
	}
}//end addAfter

template <class DataType>
void SinglyLinkedList<DataType>::addToPos(DataType newData, int pos)
{
	Node<DataType>* newNode;
	Node<DataType>* temp_f = headNode.get_Front();
	Node<DataType>* temp_b;
	if (pos <= headNode.get_nodeCounter())
	{
		if (pos == 0)
		{
			newNode = new Node<DataType>(newData, headNode.get_Front());
			headNode.set_Front(newNode);
		}
		else
		{
			for (int i = 0; i < pos - 1; i++)
			{
				temp_f = temp_f->get_next();
			}
			temp_b = temp_f;
			temp_f = temp_f->get_next();
			newNode = new Node<DataType>(newData, temp_f);
			temp_b->set_next(newNode);

		}
		if (newNode->get_next() == nullptr)headNode.set_Rear(newNode);

		++headNode;
	}
	else
	{
		cout << "Error: position not in range.\n";
	}
}//end addToPos


template <class DataType>
void SinglyLinkedList<DataType>::remove(DataType data2delete)
{
	Node<DataType>* temp_f = headNode.get_Front();
	Node<DataType>* temp_b;

	if (find(data2delete) != -1)
	{

		if (temp_f->get_data() == data2delete)
		{
			headNode.set_Front(temp_f->get_next());
			delete temp_f;
		}
		else 
		{
			while (temp_f->get_next()->get_data() != data2delete)
			{
				temp_f = temp_f->get_next();
			}
			temp_b = temp_f;
			temp_f = temp_f->get_next();
			temp_b->set_next(temp_f->get_next());
			delete temp_f;
			if (temp_b->get_next() == nullptr)headNode.set_Rear(temp_b);
		}
		--headNode;
	}
	else
	{
		cout << "The data does not exist in the list";
	}
}//end remove


template <class DataType>
int SinglyLinkedList<DataType>::find(DataType data2find)
{
	int pos = 0;
	Node<DataType>* temp = headNode.get_Front();

	while (temp != nullptr)
	{
		if (temp->get_data() == data2find) return pos;//*data2find

		temp = temp->get_next();
		pos++;
	}
	return -1;
}//end find


template <class DataType>
DataType* SinglyLinkedList<DataType>::get_node_address(DataType data2find)
{
	int pos = 0;
	Node<DataType>* temp = headNode.get_Front();

	while (temp != nullptr)
	{
		if (temp->get_data() == data2find) return temp->get_dataAddress();

		temp = temp->get_next();
		pos++;
	}
	return nullptr;
}//end find


template <class DataType>
DataType SinglyLinkedList<DataType>::get_node_data(DataType data2find)
{
	int pos = 0;
	Node<DataType>* temp = headNode.get_Front();

	while (temp != nullptr)
	{
		if (temp->get_data() == data2find) return temp->get_data();

		temp = temp->get_next();
		pos++;
	}
	return data2find;
;
}//end find


template <class DataType>
void SinglyLinkedList<DataType>::emptyList()
{
	Node<DataType>* temp_f = headNode.get_Front();
	Node<DataType>* temp_b;

	cout << "\tEmptying list:" << endl;
	while (temp_f != nullptr)
	{
		temp_b = temp_f;
		temp_f = temp_f->get_next();
		//cout << "\tRemoving " << temp_b->get_data() << endl;
		delete temp_b;
		--headNode;
	}
	headNode.set_Front(0);
	headNode.set_Rear(0);
}//end emptyList


template <class DataType>
int SinglyLinkedList<DataType>::countNodes() 
{
	return headNode.get_nodeCounter();
}//end countNodes




template <class DataType>
ostream& operator<<(ostream& s, const SinglyLinkedList<DataType>& list)
{
	Node<DataType>* temp = list.headNode.get_Front();

	while (temp != nullptr)
	{
		s << *temp->get_dataAddress() << endl;
		temp = temp->get_next();
	}
	return s;
}

