#include "HashNode.h"

template <class key_type, class value_type>
class DeletedNode : public HashNode<key_type, value_type> 
{
	private:
		static DeletedNode * entry;
		DeletedNode() : Node() {}

	public:
		static DeletedNode * getUniqueDeletedNode();
};

template <class key_type, class value_type>
DeletedNode<key_type, value_type> * DeletedNode<key_type, value_type>::getUniqueDeletedNode()
{
	if (entry == NULL)
		entry = new DeletedNode();
	return entry;
}

template <class key_type, class value_type>
DeletedNode<key_type, value_type> * DeletedNode<key_type, value_type>::entry = NULL;