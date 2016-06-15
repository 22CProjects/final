#ifndef _AVL
#define _AVL

#include "BinaryNode.h"
#include "BinarySearchTree.h"
#include <iostream>
using std::cout;
using std::endl;

template <class DataType, class KeyType>
class AVLTree : public BinarySearchTree<DataType, KeyType>
{
	protected:
		BinaryNode<DataType, KeyType>* insert(BinaryNode<DataType, KeyType>* root, BinaryNode<DataType, KeyType>* newNodePtr);

		int balanceFactor(BinaryNode<DataType, KeyType>* root);
		
		BinaryNode<DataType, KeyType>* balance(BinaryNode<DataType, KeyType>* root);

		BinaryNode<DataType, KeyType>* RR_rotation(BinaryNode<DataType, KeyType>* root);
		BinaryNode<DataType, KeyType>* LL_rotation(BinaryNode<DataType, KeyType>* root);
		BinaryNode<DataType, KeyType>* RL_rotation(BinaryNode<DataType, KeyType>* root);
		BinaryNode<DataType, KeyType>* LR_rotation(BinaryNode<DataType, KeyType>* root);

		BinaryNode<DataType, KeyType>* removeValue(BinaryNode<DataType, KeyType>* subTreePtr, KeyType targetKey, bool& success);


	public:
		//CONSTRUCTORS:
		
		AVLTree() : BinarySearchTree<DataType, KeyType>() {}
		AVLTree(const KeyType& key, DataType* rootItem) : BinarySearchTree<DataType, KeyType>(key, rootItem) {}
		AVLTree(const KeyType& key, DataType* rootItem, const BinarySearchTree<DataType, KeyType>*
			leftTreePtr, const BinarySearchTree<DataType, KeyType>* rightTreePtr) : BinarySearchTree<DataType, KeyType>(key, rootItem, leftTreePtr, rightTreePtr) {}
		AVLTree(const BinarySearchTree<DataType, KeyType>& treePtr) : BinarySearchTree<DataType, KeyType>(treePtr) {}
		//~AVLTree();


		bool avlAdd(const KeyType&, DataType*);
		bool avlRemove(KeyType target);													// Removes a node
		
		

};
#endif 

template<class DataType, class KeyType>
int AVLTree<DataType, KeyType>::balanceFactor(BinaryNode<DataType, KeyType>* root)
{
	if (root == nullptr){
		return 0;
	}
	else if (root->isLeaf()){
		return 1;
	}
	else if (root->getLeftChildPtr() == nullptr){
		return 0 - getHeightHelper(root->getRightChildPtr());
	}
	else if (root->getRightChildPtr() == nullptr){
		return getHeightHelper(root->getLeftChildPtr());
	}
	else
	return getHeightHelper(root->getLeftChildPtr()) - getHeightHelper(root->getRightChildPtr());
}

template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::RR_rotation(BinaryNode<DataType, KeyType>* root) // Rotate left
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getRightChildPtr();
	root->setRightChildPtr(nodePtr->getLeftChildPtr());
	nodePtr->setLeftChildPtr(root);
	
	return nodePtr;
}

template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::LL_rotation(BinaryNode<DataType, KeyType>* root) // Rotate right
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getLeftChildPtr();
	root->setLeftChildPtr(nodePtr->getRightChildPtr());
	nodePtr->setRightChildPtr(root);

	return nodePtr;
}

template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::RL_rotation(BinaryNode<DataType, KeyType>* root)
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getRightChildPtr();
	root->setRightChildPtr(LL_rotation(nodePtr));
	return RR_rotation(root);
}

template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::LR_rotation(BinaryNode<DataType, KeyType>* root)
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getLeftChildPtr();
	root->setLeftChildPtr(RR_rotation(nodePtr));
	return LL_rotation(root);
}


template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::balance(BinaryNode<DataType, KeyType>* root)
{
	int bal_factor = balanceFactor(root);

	if (bal_factor > 1)
	{
		if (balanceFactor(root->getLeftChildPtr()) > 0)
			root = LL_rotation(root);
		else
			root = LR_rotation(root);
	}
	else if (bal_factor < -1)
	{
		if (balanceFactor(root->getRightChildPtr()) > 0)
			root = RL_rotation(root);
		else
			root = RR_rotation(root);
	}
	return root;
}


template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::insert(BinaryNode<DataType, KeyType>* root, BinaryNode<DataType, KeyType>* newNodePtr)
{
	if (root == nullptr){
		return newNodePtr;
	}
		
	else if (newNodePtr->get_key() < root->get_key()){
		root->setLeftChildPtr(insert(root->getLeftChildPtr(), newNodePtr));
	}
		
	else{
		root->setRightChildPtr(insert(root->getRightChildPtr(), newNodePtr));
	}

	return balance(root);
}

template<class DataType, class KeyType>
bool AVLTree<DataType, KeyType>::avlAdd(const KeyType& newKey, DataType* newData)
{
	BinaryNode<DataType, KeyType>* newNodePtr = new BinaryNode<DataType, KeyType>(newKey, newData);
	set_rootPtr(insert(getRootPtr(), newNodePtr));
	nodeCounter++;
	return true;
}


// REMOVE
template< class DataType, class KeyType>
bool AVLTree<DataType, KeyType>::avlRemove(KeyType target)
{
	bool success = false;
	set_rootPtr(removeValue(getRootPtr(), target, success));
	if (success == true) nodeCounter--;
	return success;
} // end remove


// REMOVE VALUE
template< class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::
removeValue(BinaryNode<DataType, KeyType>* subTreePtr, KeyType targetKey, bool& success)
{
	BinaryNode<DataType, KeyType>* tempPtr = nullptr;

	if (subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}
	else if (subTreePtr->get_key() == targetKey)
	{
		// Item is in the root of some subtree
		subTreePtr = removeNode(subTreePtr); // Remove item
		success = true;
	}
	else if (subTreePtr->get_key() > targetKey)
	{
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), targetKey, success);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		tempPtr = removeValue(subTreePtr->getRightChildPtr(), targetKey, success);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	return balance(subTreePtr);
} // End remove value