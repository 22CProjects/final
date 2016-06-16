#pragma once

#include "BinaryNode.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

template<class DataType, class KeyType>
class BinarySearchTree
{
	private:
		
	protected:
		BinaryNode<DataType, KeyType>* rootPtr;	// point to the highest root of the tree
		int nodeCounter;
		/*************************************************************************************
			getHeightHelper - Protected
			- Recursively goes through the tree to count the height of the tree
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
			- Return: an int (the height)
		*************************************************************************************/
		int getHeightHelper(BinaryNode<DataType, KeyType>* subTreePtr);


		
		/*************************************************************************************
			destroyTree - Protected
			- Recursively deletes all nodes from the tree.
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
			- Return: none
		*************************************************************************************/
		void destroyTree(BinaryNode<DataType, KeyType>* subTreePtr);


		
		/*************************************************************************************
			insertInorder - Protected
			- Recursively adds a new node to the tree in a left/right fashion to keep the tree balanced. 
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
				+ a BinaryNode pointer to new node needed to be inserted
			- Return: a BinaryNode pointer
		*************************************************************************************/
		BinaryNode<DataType, KeyType>* insertInorder(BinaryNode<DataType, KeyType>* subTreePtr, BinaryNode<DataType, KeyType>* newNodePtr);

		

		/*************************************************************************************
			removeValue - Protected
			- It removes value indicated in the parameter 
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
				+ an int contain the key of data needs to be removed
				+ a booline to indicate success or not
			- Return: a BinaryNode pointer

			removeValue calls removeNode calls removeLeftMostNode
		*************************************************************************************/
		virtual BinaryNode<DataType, KeyType>* removeValue(BinaryNode<DataType, KeyType>* subTreePtr, KeyType targetKey, bool& success);
		BinaryNode<DataType, KeyType>* removeNode(BinaryNode<DataType, KeyType>* nodePtr);
		BinaryNode<DataType, KeyType>* removeLeftMostNode(BinaryNode<DataType, KeyType>* nodePtr, KeyType& successorKey, DataType* inorderSuccesssorPtr);


		
		/*************************************************************************************
			findNode - Protected
			- Recursively searches for target value in the tree by using a preorder traversal.
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
				+ a DataType value needs to be found
				+ a booline to indicate successfully found or not
			- Return: a BinaryNode pointer to the node found
		*************************************************************************************/
		BinaryNode<DataType, KeyType>* findNode(BinaryNode<DataType, KeyType>* treePtr, const KeyType& targetKey, bool& success, int& count);


		
		/*************************************************************************************
			CopyTree - Protected
			- Copies the tree rooted at treePtr
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
			- Return: a BinaryNode pointer of the new copied tree

			Mainly used in constructors
		*************************************************************************************/
		BinaryNode<DataType, KeyType>*copyTree(const BinaryNode<DataType, KeyType>* treePtr) const;



		// RECURSIVE TRAVERAL HELPER METHODS:

			/*************************************************************************************
				IN ORDER - Protected
					- It recursively traverse inorder through the tree
					- Parameters:
						+ a void function visit that takes DataType parameter
						+ a BinaryNode pointer to a particular node of the tree
					- Return: none

				Algorithm Inorder(tree)
				1. Traverse the left subtree, i.e., call Inorder(left-subtree)
				2. Visit the root.
				3. Traverse the right subtree, i.e., call Inorder(right-subtree)
			*************************************************************************************/
			void inorder(void visit(int&), BinaryNode<DataType, KeyType>* treePtr, int& count) const;


			/*************************************************************************************
				PRE ORDER - Protected
					- It recursively traverse preorder through the tree
					- Parameters:
						+ a void function visit that takes DataType parameter
						+ a BinaryNode pointer to a particular node of the tree
					- Return: none

				Algorithm Preorder(tree)
				1. Visit the root.
				2. Traverse the left subtree, i.e., call Preorder(left-subtree)
				3. Traverse the right subtree, i.e., call Preorder(right-subtree)
			*************************************************************************************/
			void preorder(void visit(int&), BinaryNode<DataType, KeyType>* treePtr) const;


			/*************************************************************************************
			POST ORDER - Protected
				- It recursively traverse postorder through the tree
				- Parameters:
					+ a void function visit that takes DataType parameter
					+ a BinaryNode pointer to a particular node of the tree
				- Return: none

				Algorithm Postorder(tree)
				1. Traverse the left subtree, i.e., call Postorder(left-subtree)
				2. Traverse the right subtree, i.e., call Postorder(right-subtree)
				3. Visit the root.
			*************************************************************************************/
			void postorder(void visit(int&), BinaryNode<DataType, KeyType>* treePtr) const;



		/*************************************************************************************
			SAVE TO FILE - Protected
			- Save information of the tree to a text file
			- Parameters:
				+ A BinaryNode pointer - to the root 
				+ a reference of ofstream - to save the file to it
			- Return: none
		*************************************************************************************/
		void save_to_file_helper(BinaryNode<DataType, KeyType>* subTreePtr, ofstream& outputFile);


		/*************************************************************************************
			MAX - Protected
			- Compares and returns the bigger of the two number
			- Parameters:
				+ 2 integers
			- Return: an int - the bigger number
		*************************************************************************************/
		int max(int l, int r);


		/*************************************************************************************
			PRINT INDENTED TREE - Protected
			- Display the indented tree to the screen
			- Parameters:
				+ A BinaryNode pointer - to the root
				+ An int - level of the node 
			- Return: none
		*************************************************************************************/
		void print_helper(BinaryNode<DataType, KeyType>* root, int level);



	public:
		//------------------------------------------------------------
		// Constructor and Destructor Section.
		//------------------------------------------------------------
		BinarySearchTree() : rootPtr(nullptr), nodeCounter(0) {}

		BinarySearchTree(const KeyType newKey, DataType* newDataPtr);

		BinarySearchTree(const KeyType newKey, DataType* newDataPtr, const BinarySearchTree<DataType, KeyType>*
			leftTreePtr, const BinarySearchTree<DataType, KeyType>* rightTreePtr); // Definition below

		BinarySearchTree(const BinarySearchTree<DataType, KeyType>& treePtr) { rootPtr = copyTree(treePtr.rootPtr); }// copy constructor
		~BinarySearchTree()													 { destroyTree(rootPtr); }				 // Destructor


		//------------------------------------------------------------
		// Public BinaryTreeInterface Methods Section.
		//------------------------------------------------------------
		bool isEmpty() const			{ if (nodeCounter < 1) return true; else return false; }// True: tree empty
		int getHeight()					{ return getHeightHelper(rootPtr); }					// Get height of the tree
		int getNumberOfNodes() const	{ return nodeCounter; }									// Total nodes in the tree
		
		void set_rootPtr(BinaryNode<DataType, KeyType>* aNode)	{ rootPtr = aNode; }

		BinaryNode<DataType, KeyType>* getRootPtr(){ return rootPtr; }							// Get the address of the highest root

		bool add(const KeyType newKey, DataType* newDataPtr);									// Adds a node
		bool remove(KeyType targetKey);															// Removes a node
		void clear() { destroyTree(rootPtr); }													// Delete all nodes of the tree

		DataType* getEntry_address(const KeyType& anEntryKey, int& count);						// Get address of a data
		bool is_contained(const KeyType& anEntryKey);											// Check if an entry is existed in the tree
		



		//------------------------------------------------------------
		// Public Traversals Section.
		//------------------------------------------------------------
		int  inorderTraverse(void visit(int&)) const	{ int count = 0; inorder(visit, rootPtr, count); return count; }
		void postorderTraverse(void visit(int&)) const	{ postorder(visit, rootPtr); }
		void preorderTraverse(void visit(int&)) const	{ preorder(visit, rootPtr); }

		/****************************************************************************
			Definition of save_to_file
			 - It calls save_toFile_helper to go through the tree, and save
			   the content of data to the outputFile
			 - Parameter: a reference ofstream object
			 - Output: none
		****************************************************************************/
		
		void save_to_file(ofstream& outputFile)			{ save_to_file_helper(rootPtr, outputFile); }

		/****************************************************************************
			Definition of save_to_file
			- prints an indented tree to the consol
			- Parameter: none
			- Output: none
		****************************************************************************/
		void print_tree()								{	print_helper(rootPtr, 0); }
};
// !_BinarySearchTree

// CONSTRUCTOR2 - Public
template<class DataType, class KeyType>
BinarySearchTree<DataType, KeyType>::BinarySearchTree(const KeyType newKey, DataType* newDataPtr)
{ 
	rootPtr = new BinaryNode<DataType, KeyType>(newKey, newDataPtr, nullptr, nullptr); 
	nodeCounter++; 
}

// CONSTRUCTOR3 - Public
template<class DataType, class KeyType>
BinarySearchTree<DataType, KeyType>::BinarySearchTree(const KeyType newKey, DataType* newDataPtr,
	const BinarySearchTree<DataType, KeyType>* leftTreePtr,
	const BinarySearchTree<DataType, KeyType>* rightTreePtr)
{
	nodeCounter = 0;
	rootPtr = new BinaryNode<DataType, KeyType>(newKey, newDataPtr, copyTree(leftTreePtr->rootPtr),
		copyTree(rightTreePtr->rootPtr));
	nodeCounter++;
}

// COPYTREE
template< class DataType, class KeyType>
BinaryNode<DataType, KeyType>* BinarySearchTree<DataType, KeyType>::copyTree(const BinaryNode<DataType, KeyType>* treePtr) const
{
	BinaryNode<DataType, KeyType>* newTreePtr = nullptr;
	// Copy tree nodes during a preorder traversal
	if (treePtr != nullptr)
	{
		// Copy node
		newTreePtr = new BinaryNode<DataType, KeyType>(treePtr->get_key(), treePtr->getItemPtr(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	} // end if
	// Else tree is empty (newTreePtr is nullptr)
	return newTreePtr;
} // end copyTree 



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		GET HEIGHT
//		 - And supporting function
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// MAX FUNCTION for getHeightHelper
	template< class DataType, class KeyType>
	int BinarySearchTree<DataType, KeyType>::max(int l, int r)
	{
		if (l > r) return l;
		else return r;
	}

	// GET HEIGHT
	template< class DataType, class KeyType>
	int BinarySearchTree<DataType, KeyType>::getHeightHelper(BinaryNode<DataType, KeyType>* subTreePtr)
	{
		if (subTreePtr == nullptr)
			return 0;
		else
			return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()),
				getHeightHelper(subTreePtr->getRightChildPtr()));
	} // end getHeightHelper 



//DESTROY TREE - Protected
template< class DataType, class KeyType>
void BinarySearchTree<DataType, KeyType>::destroyTree(BinaryNode<DataType, KeyType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		cout << "Deleted " << subTreePtr->get_key() << endl;
		delete subTreePtr;
		nodeCounter--;
	} // end if
	rootPtr = nullptr;
} // end destroyTree 



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		GET ENTRY & CONTAIN
//		 - And supporting function
//			+ findNode - protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// FIND NODE
	template<class DataType, class KeyType>
	BinaryNode<DataType, KeyType>* BinarySearchTree<DataType, KeyType>::findNode(BinaryNode<DataType, KeyType>* treePtr, const KeyType& targetKey, bool& success, int& count)
	{
		++count;
		if (treePtr == nullptr)
		{
			success = false;
			return nullptr;
		}

		if (targetKey == treePtr->get_key())
		{
			success = true;
			return treePtr;
		}

		else if (targetKey < treePtr->get_key())
			return findNode(treePtr->getLeftChildPtr(), targetKey, success, count);
		else
			return findNode(treePtr->getRightChildPtr(), targetKey, success, count);

	} // end findNode


	// GET ENTRY
	template<class DataType, class KeyType>
	DataType* BinarySearchTree<DataType, KeyType>::getEntry_address(const KeyType& anEntryKey, int& count)
	{
		bool isFound = false;
		BinaryNode<DataType, KeyType>* entry_address = findNode(rootPtr, anEntryKey, isFound, count);
		return entry_address->getItemPtr();
	}

	// IS CONTAINED?
	template<class DataType, class KeyType>
	bool BinarySearchTree<DataType, KeyType>::is_contained(const KeyType& anEntryKey)
	{
		bool isFound = false;
		int count = 0;
		BinaryNode<DataType, KeyType>* result = findNode(rootPtr, anEntryKey, isFound, count);
		return isFound;
	}






//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		ADD - Public
//		 - and supporting add method: INSERT INORDER - Protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// ADD
	template< class DataType, class KeyType>
	bool BinarySearchTree<DataType, KeyType>::add(const KeyType newKey, DataType* newDataPtr)
	{
		BinaryNode<DataType, KeyType>* newNodePtr = new BinaryNode<DataType, KeyType>(newKey, newDataPtr);
		rootPtr = insertInorder(rootPtr, newNodePtr);
		nodeCounter++;
		cout << "Added " << newKey << " Total Nodes: " << nodeCounter << endl;
		return true;
	} // end add

	// INSERT INORDER - for ADD
	template< class DataType, class KeyType>
	BinaryNode<DataType, KeyType>* BinarySearchTree<DataType, KeyType>::
		insertInorder(BinaryNode<DataType, KeyType>* subTreePtr, BinaryNode<DataType, KeyType>* newNodePtr)
	{
		BinaryNode<DataType, KeyType>* tempPtr = nullptr;

		if (subTreePtr == nullptr)
			return newNodePtr;

		else if (subTreePtr->get_key() > newNodePtr->get_key())
		{
			tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
			subTreePtr->setLeftChildPtr(tempPtr);
		}
		else
		{
			tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
			subTreePtr->setRightChildPtr(tempPtr);
		}
		return subTreePtr;
	}




//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		REMOVE - Public
//		 - and supporting methods: 
//			+ removeValue - Protected
//			+ removeNode  - Protected 
//			+ removeLeftMostNode - Protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// REMOVE
	template< class DataType, class KeyType>
	bool BinarySearchTree<DataType, KeyType>::remove(KeyType targetKey)
	{
		bool success = false;
		rootPtr = removeValue(rootPtr, targetKey, success);
		if (success == true) nodeCounter--;
		return success;
	} // end remove

	// REMOVE VALUE
	template< class DataType, class KeyType>
	BinaryNode<DataType, KeyType>* BinarySearchTree<DataType, KeyType>::
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
			return subTreePtr;
		}
		else if (subTreePtr->get_key() > targetKey)
		{
			tempPtr = removeValue(subTreePtr->getLeftChildPtr(), targetKey, success);
			subTreePtr->setLeftChildPtr(tempPtr);
			return subTreePtr;
		}
		else
		{
			tempPtr = removeValue(subTreePtr->getRightChildPtr(), targetKey, success);
			subTreePtr->setRightChildPtr(tempPtr);
			return subTreePtr;
		}
	} // End remove value

	// REMOVE NODE
	template< class DataType, class KeyType>
	BinaryNode<DataType, KeyType>* BinarySearchTree<DataType, KeyType>::removeNode(BinaryNode<DataType, KeyType>* nodePtr)
	{
		BinaryNode<DataType, KeyType>* tempPtr = nullptr;
		if (nodePtr->isLeaf() == true)
		{
			//Remove leaf from the tree
			delete nodePtr;
			nodePtr = nullptr;
			return nodePtr;
		}
		else if (nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() != nullptr) // has two children
		{
			BinaryNode<DataType, KeyType>* temp = nodePtr->getRightChildPtr();
			

			if (temp->isLeaf() == true)
			{
				nodePtr->setItemPtr(temp->getItemPtr());
				nodePtr->set_key(temp->get_key());
				nodePtr->setRightChildPtr(nullptr);
			}
			else if (temp->getLeftChildPtr() == nullptr && temp->getRightChildPtr() != nullptr)
			{
				BinaryNode<DataType, KeyType>* temp_R = temp->getRightChildPtr();
				nodePtr->setItemPtr(temp->getItemPtr());
				nodePtr->set_key(temp->get_key());
				nodePtr->setRightChildPtr(temp_R);
			}
			else if (temp->getLeftChildPtr()->getLeftChildPtr() == nullptr)
			{
				BinaryNode<DataType, KeyType>* temp_L = temp->getLeftChildPtr();
				nodePtr->setItemPtr(temp_L->getItemPtr());
				nodePtr->set_key(temp_L->get_key());
				temp->setLeftChildPtr(nullptr);
			}
			else
			{
				BinaryNode<DataType, KeyType>* temp_L = temp->getLeftChildPtr();
				BinaryNode<DataType, KeyType>* temp_LL = temp_L->getLeftChildPtr();
				while (temp_LL->getLeftChildPtr() != nullptr)
				{
					temp = temp_L;
					temp_L = temp_LL;
					temp_LL = temp_LL->getLeftChildPtr();
				}
				nodePtr->setItemPtr(temp_LL->getItemPtr());
				nodePtr->set_key(temp_LL->get_key());
				temp_L->setLeftChildPtr(nullptr);
			}
			

			
			return nodePtr;
		}
		else
		{
			if (nodePtr->getLeftChildPtr() != nullptr)
			{
				tempPtr = nodePtr->getLeftChildPtr();
				return tempPtr;
			}
				
			else
			{
				tempPtr = nodePtr->getRightChildPtr();
				delete nodePtr;
				nodePtr = nullptr;
				return tempPtr;
			}
		}
	} // End removeNode


	// REMOVE LEFT MOST NODE
	template< class DataType, class KeyType>
	BinaryNode<DataType, KeyType>* BinarySearchTree<DataType, KeyType>::
		removeLeftMostNode(BinaryNode<DataType, KeyType>* nodePtr, KeyType& successorKey, DataType* inorderSuccesssorPtr)
	{
		if (nodePtr->getLeftChildPtr() == nullptr)
		{
			inorderSuccesssorPtr = nodePtr->getItemPtr();
			successorKey = nodePtr->get_key();
			return removeNode(nodePtr);
		}
		else
			return removeLeftMostNode(nodePtr->getLeftChildPtr(), successorKey, inorderSuccesssorPtr);
	} // End remove left most node





//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		TRAVERAL methods - protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

	// IN ORDER
	template< class DataType, class KeyType>
	void BinarySearchTree<DataType, KeyType>::inorder(void visit(int&), BinaryNode<DataType, KeyType>* treePtr, int& count) const
	{
		++count;
		if (treePtr != nullptr)
		{
			inorder(visit, treePtr->getLeftChildPtr(), count);

			KeyType theItemKey = treePtr->get_key();
			visit(theItemKey);

			inorder(visit, treePtr->getRightChildPtr(), count);

		} // end if
	} // end inorder 



	// PRE ORDER
	template< class DataType, class KeyType>
	void BinarySearchTree<DataType, KeyType>::preorder(void visit(int&), BinaryNode<DataType, KeyType>* treePtr) const
	{
		if (treePtr != nullptr)
		{
			KeyType theItemKey = treePtr->get_key();
			visit(theItemKey);

			preorder(visit, treePtr->getLeftChildPtr());

			preorder(visit, treePtr->getRightChildPtr());

		} // end if
	} // end preorder 


	// POST ORDER
	template< class DataType, class KeyType>
	void BinarySearchTree<DataType, KeyType>::postorder(void visit(int&), BinaryNode<DataType, KeyType>* treePtr) const
	{
		if (treePtr != nullptr)
		{
			postorder(visit, treePtr->getLeftChildPtr());

			postorder(visit, treePtr->getRightChildPtr());

			KeyType theItemKey = treePtr->get_key();
			visit(theItemKey);

		} // end if
	} // end postorder 


// PRINT INDENTED TREE - protected (print_helper)
template<class DataType, class KeyType>
void  BinarySearchTree<DataType, KeyType>::print_helper(BinaryNode<DataType, KeyType>* root, int level){
	if (root == nullptr)
			return;
	print_helper(root->getRightChildPtr(), level + 1);
	if (level != 0){
		for (int i = 0; i < level - 1; i++){
			cout<<"|\t";
		}
		cout<<"|-------" << root->get_key()<<endl;
	}
	else
		cout<<root->get_key()<<endl;
	print_helper(root->getLeftChildPtr(), level + 1);
} // End print_helper


// SAVE TO FILE
template<class DataType, class KeyType>
void BinarySearchTree<DataType, KeyType>::save_to_file_helper(BinaryNode<DataType, KeyType>* subTreePtr, ofstream& outputFile)
{
	if (subTreePtr == nullptr)
		return;
	else
	{
		outputFile << *subTreePtr->getItemPtr()<<endl;
		save_to_file_helper(subTreePtr->getLeftChildPtr(), outputFile);
		save_to_file_helper(subTreePtr->getRightChildPtr(), outputFile);
	}
}



