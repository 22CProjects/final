#include "HashNode.h"

template <class key_type, class value_type>
class DeletedNode : public HashNode<key_type, value_type>
{
private:
	static DeletedNode * entry; // creating an entry to be used as the deleted node
	DeletedNode() : HashNode() {} // using the constructor from the hash node class

public:
	static DeletedNode * getUniqueDeletedNode();
};

// Function to create a new unique deleted node everytime the function is called
// this is to make sure the deleted node is accounted for in the hash table when a node is deleted
template <class key_type, class value_type>
DeletedNode<key_type, value_type> * DeletedNode<key_type, value_type>::getUniqueDeletedNode()
{
	if (entry == NULL)
		entry = new DeletedNode(); 
	return entry;
}

// creation of a deleted node pointer to null 
template <class key_type, class value_type>
DeletedNode<key_type, value_type> * DeletedNode<key_type, value_type>::entry = NULL; 
