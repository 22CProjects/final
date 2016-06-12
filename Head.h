/* Specification and implementation of Head ADT (Derived from Node) */
#ifndef _HEAD
#define _HEAD

#include "Node.h"

template <class DataType>
class Head : public Node<DataType>
{
private:
	Node* rear;			// Point to the node at the end of the list
	Node* front;		// Point to the node at the beginning of the list
	int nodeCounter;	// To hold the number of nodes in the list
public:

	// Default constructor: Initialize nodeCounter to 0 and point rear & front to nullptr
	Head() :  Node<DataType>()
	{
		nodeCounter = 0;
		rear = nullptr;
		front = nullptr;
	}

	// Destructor
	~Head() {}
	
	// Overloaded operators
	Head& operator++() { nodeCounter++; return *this; }
	Head& operator--() { nodeCounter--; return *this; }

	// Mutators
	void set_Front(Node* node) { front = node; }
	void set_Rear(Node* node) { rear = node; } 

	// Accessors
	int   get_nodeCounter() { return nodeCounter; }
	Node* get_Front() const { return front; }
	Node* get_Rear() const { return rear; }
};
#endif // !_HEAD
