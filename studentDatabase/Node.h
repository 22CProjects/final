/*	Anna Houk, Kiera Nguyen, Michael Phan*/
/* Specification and implementation of Node ADT */
#ifndef _NODE
#define _NODE

template <class DataType>
class Node
{
protected:
	DataType data;	// To hold data
	Node *nextNode;	// To point to the next node in the list

public:
	// Default constructor
	Node() : nextNode(0) {}		// Initialize nextNode pointer to nullptr

	// Overloaded constructor: Initialize data, and nextNode to parameter d and n
	Node(DataType d, Node* n) : data(d), nextNode(n) {}

	// Destructor
	~Node(){}

	// Mutator
	void     set_next(Node* ptr) { nextNode = ptr; }

	// Accessors
	DataType get_data() const { return data; }
	DataType* get_dataAddress()  { return &data; }
	Node*    get_next() const { return nextNode; }
	
};
#endif // !_NODE
