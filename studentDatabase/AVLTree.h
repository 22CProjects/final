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
		/*********************************************************************
			Rotation methods 
			  - Parameter: a BinaryNode pointer point to a node of the tree
			  - Return: a BinaryNode pointer
		*********************************************************************/
		BinaryNode<DataType, KeyType>* RR_rotation(BinaryNode<DataType, KeyType>* root);	// Left Rotation
		BinaryNode<DataType, KeyType>* LL_rotation(BinaryNode<DataType, KeyType>* root);	// Right Rotation
		BinaryNode<DataType, KeyType>* RL_rotation(BinaryNode<DataType, KeyType>* root);	// Right then left rotation
		BinaryNode<DataType, KeyType>* LR_rotation(BinaryNode<DataType, KeyType>* root);	// Left then right rotation
		
		/*********************************************************************
			balanceFactor
				- Calculates and returns the difference in height of 2 branches
				- Parameter: a BinaryNode pointer point to a node of the tree
				- Return: an integer (difference in height)
		*********************************************************************/
		int balanceFactor(BinaryNode<DataType, KeyType>* root);
		
		/*********************************************************************
			balance
			- bases on the height difference calculated in balanceFactor
			  the tree will rotate right or left accordingly to make it balance
			- Parameter: a BinaryNode pointer point to a node of the tree
			- Return: a BinaryNode pointer
		*********************************************************************/
		BinaryNode<DataType, KeyType>* balance(BinaryNode<DataType, KeyType>* root);

		/*********************************************************************
			insert
			- it inserts a newnode, and balance it if it's imbalance
			- Parameter: 
			    + a BinaryNode pointer point to a node of the tree
				+ a BinaryNode pointer point to the new node to insert
			- Return: a BinaryNode pointer
		*********************************************************************/
		BinaryNode<DataType, KeyType>* insert(BinaryNode<DataType, KeyType>* root, BinaryNode<DataType, KeyType>* newNodePtr, int& count);
		
		/*********************************************************************
			removeValue
			- instead of just return subTreePtr, this virtual function derived 
			  from BST returns balance(subTreePtr) to balance the tree after 
			  delete a node
		*********************************************************************/
		BinaryNode<DataType, KeyType>* removeValue(BinaryNode<DataType, KeyType>* subTreePtr, KeyType targetKey, bool& success, int& count);
		

	public:
		//CONSTRUCTORS:
		
		AVLTree() : BinarySearchTree<DataType, KeyType>() {}
		AVLTree(const KeyType& key, DataType* rootItem) : BinarySearchTree<DataType, KeyType>(key, rootItem) {}
		AVLTree(const KeyType& key, DataType* rootItem, const BinarySearchTree<DataType, KeyType>*
			leftTreePtr, const BinarySearchTree<DataType, KeyType>* rightTreePtr) : BinarySearchTree<DataType, KeyType>(key, rootItem, leftTreePtr, rightTreePtr) {}
		AVLTree(const BinarySearchTree<DataType, KeyType>& treePtr) : BinarySearchTree<DataType, KeyType>(treePtr) {}
		//~AVLTree();


		bool avlAdd(const KeyType&, DataType*,int& count);			// to add a new node from main
		bool avlRemove(KeyType target, int& count);					// to removes a node from main
		
		

};
#endif 

// BALANCE FACTOR
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
} // End balanceFactor


// LEFT ROTATION
template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::RR_rotation(BinaryNode<DataType, KeyType>* root) 
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getRightChildPtr();
	root->setRightChildPtr(nodePtr->getLeftChildPtr());
	nodePtr->setLeftChildPtr(root);
	
	return nodePtr;
} // end left rotation


// RIGHT ROTATION
template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::LL_rotation(BinaryNode<DataType, KeyType>* root) 
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getLeftChildPtr();
	root->setLeftChildPtr(nodePtr->getRightChildPtr());
	nodePtr->setRightChildPtr(root);

	return nodePtr;
} // End right rotation


// RIGHT --> LEFT
template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::RL_rotation(BinaryNode<DataType, KeyType>* root)
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getRightChildPtr();
	root->setRightChildPtr(LL_rotation(nodePtr));
	return RR_rotation(root);
}// end RL_rotation


// LEFT --> RIGHT
template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::LR_rotation(BinaryNode<DataType, KeyType>* root)
{
	BinaryNode<DataType, KeyType>* nodePtr = root->getLeftChildPtr();
	root->setLeftChildPtr(RR_rotation(nodePtr));
	return LL_rotation(root);
} // end LR_rotation


// BALANCE the tree
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
}// end balance


// INSERT a node to the tree, and balance if the tree is imbalance
template<class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::insert(BinaryNode<DataType, KeyType>* root, BinaryNode<DataType, KeyType>* newNodePtr, int& count)
{
	++count;
	if (root == nullptr){
		return newNodePtr;
	}

	else if (newNodePtr->get_key() < root->get_key()){
		root->setLeftChildPtr(insert(root->getLeftChildPtr(), newNodePtr, count));
	}

	else{
		root->setRightChildPtr(insert(root->getRightChildPtr(), newNodePtr, count));
	}

	return balance(root);
}


// avlAdd
template<class DataType, class KeyType>
bool AVLTree<DataType, KeyType>::avlAdd(const KeyType& newKey, DataType* newData, int& count)
{
	BinaryNode<DataType, KeyType>* newNodePtr = new BinaryNode<DataType, KeyType>(newKey, newData);
	set_rootPtr(insert(getRootPtr(), newNodePtr, count));
	nodeCounter++;
	return true;
}


// REMOVE
template< class DataType, class KeyType>
bool AVLTree<DataType, KeyType>::avlRemove(KeyType target, int& count)
{
	bool success = false;
	set_rootPtr(removeValue(getRootPtr(), target, success, count));
	if (success == true) nodeCounter--;
	return success;
} // end remove


// REMOVE VALUE
template< class DataType, class KeyType>
BinaryNode<DataType, KeyType>* AVLTree<DataType, KeyType>::
removeValue(BinaryNode<DataType, KeyType>* subTreePtr, KeyType targetKey, bool& success, int& count)
{
	BinaryNode<DataType, KeyType>* tempPtr = nullptr;
	++count;
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
		tempPtr = removeValue(subTreePtr->getLeftChildPtr(), targetKey, success, count);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		tempPtr = removeValue(subTreePtr->getRightChildPtr(), targetKey, success, count);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	return balance(subTreePtr);
} // End remove value