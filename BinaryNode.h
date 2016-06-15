#ifndef _BINARYNODE
#define _BINARYNODE

template<class DataType,class KeyType>
class BinaryNode
{
private:
	KeyType key;									// The key to sort data to the tree
	DataType* itemPtr;								// Pointer to Data
	BinaryNode<DataType, KeyType>* leftChildPtr = nullptr;	// Pointer to left child
	BinaryNode<DataType, KeyType>* rightChildPtr = nullptr;	// Pointer to right child

public:
	// Default constructor: initialize two right and left pointer to nullptr
	BinaryNode() :leftChildPtr(nullptr), rightChildPtr(nullptr), itemPtr(0), key(0){}
	// Constructor 1: initialize item = anItem input, and two right and left pointer to nullptr
	BinaryNode(const KeyType k, DataType* anItemPtr) : key(k), itemPtr(anItemPtr), leftChildPtr(nullptr), rightChildPtr(nullptr){}
	// Constructor 2: initialize item, right pointer and left pointer equal to the according parameters 
	BinaryNode(const KeyType k, const DataType* anItemPtr, BinaryNode<DataType, KeyType>* leftPtr, BinaryNode<DataType, KeyType>* rightPtr) :
		key(k), itemPtr(anItemPtr), leftChildPtr(leftPtr), rightChildPtr(rightPtr){}

	// Check if the node is a leaf (left and right pointers point to null)
	bool isLeaf() const
	{
		if (leftChildPtr == nullptr && rightChildPtr == nullptr)
			return true;
		else return false;
	}

	// Mutators
	KeyType get_key() const									{ return key; }
	DataType* getItemPtr() const							{ return itemPtr; }
	BinaryNode<DataType, KeyType>* getLeftChildPtr() const	{ return leftChildPtr; }
	BinaryNode<DataType, KeyType>* getRightChildPtr() const	{ return rightChildPtr; }

	// Accessors
	void set_key(KeyType k)									{ key = k; }
	void setItemPtr(DataType* anItemPtr)					{ itemPtr = anItemPtr; }
	void setLeftChildPtr(BinaryNode<DataType, KeyType>* leftPtr)	{ leftChildPtr = leftPtr; }
	void setRightChildPtr(BinaryNode<DataType, KeyType>* rightPtr)	{ rightChildPtr = rightPtr; }


};
#endif // !_BINARYNODE

