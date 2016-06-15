#ifndef HASTTABLE_H
#define HASTTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "HashNode.h"
#include "DeletedNode.h"

const int HASH_TABLE_SIZE = 40;

//Creation of the hash table class
template <class key_type, class value_type>
class HashTable
{
	private:
		Node<key_type, value_type> ** hash_table;		// creation of the hash table
		int pseudo_array[HASH_TABLE_SIZE];    // created an array to hold a random set of numbers to
																					// use pseudo random probing

	public:
		HashTable();		// default constructor
		~HashTable();		// deconstructor
		void insert(key_type key, value_type value);  // creation of the insertion function to input data in to the hash table
		value_type find(key_type key);		// creation of the function to find the object by the key
		void remove(key_type key);			// creation of the function to remove an element from the hash table
		void print_table();			// function to print the table in hash order
		void save_to_file(ofstream & output_file);   // function to print the hash table to a file
};

// The default constructor
template <class key_type, class value_type>
HashTable<key_type, value_type>::HashTable()
{
	hash_table = new Node<key_type, value_type>*[HASH_TABLE_SIZE]; // dynamic allocation for the hash table
	srand( (unsigned int)time(NULL) ); // using the srand function and time function to get different random everytime the program is ran
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		hash_table[i] = NULL; // setting every element in the hash table to null
		int x = rand() % 30; // picking a random number between 0-29 to put into the pseudo random array
		pseudo_array[i] = x; // putting the random number in to the array
	}

}

// The deconstructor
template <class key_type, class value_type>
HashTable<key_type, value_type>::~HashTable()
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (hash_table[i] != NULL && hash_table[i] != DeletedNode<key_type, value_type>::getUniqueDeletedNode()) //checking if the element is equal to
																																																						// null or a deleted node
		{
			delete hash_table[i]; // deleting every element in the hash table
		}
	}

	delete[] hash_table;  // deleting the hash table
}


// Insertion function
template <class key_type, class value_type>
void HashTable<key_type, value_type>::insert(key_type key, value_type value)
{
	int hash_key = (key % HASH_TABLE_SIZE); // the hash function
	int first_hash = -1;
	int deleted_node = -1;
	int counter = 0;

	while (hash_key != first_hash && (hash_table[hash_key] == DeletedNode<key_type, value_type>::getUniqueDeletedNode() || hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() != key))
	// checking if the element is equal to null or a deleted node
	{
		if (first_hash == -1)
		{
			first_hash = hash_key;
		}

		if (hash_table[hash_key] == DeletedNode<key_type, value_type>::getUniqueDeletedNode())
		{
			deleted_node = hash_key;
		}

		counter++;
		hash_key = (hash_key + pseudo_array[counter]) % HASH_TABLE_SIZE;  // using pseudo random probing to deal with collision
	}

	if ((hash_table[hash_key] == NULL || hash_key == first_hash) && deleted_node != -1)
	{
		hash_table[deleted_node] = new Node<key_type, value_type>(key, value); // if equal to deleted node, create a new node in the location
	}
	else if (first_hash != hash_key)
	{
		if (hash_table[hash_key] != DeletedNode<key_type, value_type>::getUniqueDeletedNode() && hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() == key)
		{
			hash_table[hash_key]->set_value(value);
		}
		else
		{
			hash_table[hash_key] = new Node<key_type, value_type>(key, value);
		}
	}
}


// The find function
template <class key_type, class value_type>
value_type HashTable<key_type, value_type>::find(key_type key)
{
	int hash_key = (key % HASH_TABLE_SIZE);
	int first_hash = -1;
	int counter = 0;
	while (hash_key != first_hash && (hash_table[hash_key] == DeletedNode<key_type, value_type>::getUniqueDeletedNode() || hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() != key))
	{
		if (first_hash == -1)
		{
			first_hash = hash_key;
		}

		counter++;
		hash_key = (hash_key + pseudo_array[counter]) % HASH_TABLE_SIZE; // pseudo random probing
	}
	if (hash_table[hash_key] == NULL || hash_key == first_hash)
	{
		cout << "Key not found" << endl;
	}
	else
	{
		cout << hash_table[hash_key]->get_value() << endl;
		return hash_table[hash_key]->get_value();  // returning the hash table key
	}
}

// The remove function
template <class key_type, class value_type>
void HashTable<key_type, value_type>::remove(key_type key)
{
	int hash_key = (key % HASH_TABLE_SIZE);
	int first_hash = -1;
	int counter = 0;

	while (hash_key != first_hash && (hash_table[hash_key] == DeletedNode<key_type, value_type>::getUniqueDeletedNode() || hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() != key)) {
		if (first_hash == -1)
		{
			first_hash = hash_key;
		}

		counter++;
		hash_key = (hash_key + pseudo_array[counter]) % HASH_TABLE_SIZE;;  // pseudo random probing
	}
	if (hash_key != first_hash && hash_table[hash_key] != NULL)
	{
		delete hash_table[hash_key];
		hash_table[hash_key] = DeletedNode<key_type, value_type>::getUniqueDeletedNode();
	}
}


// Print table function
template <class key_type, class value_type>
void HashTable<key_type, value_type>::print_table()
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (hash_table[i] == DeletedNode<key_type, value_type>::getUniqueDeletedNode() || hash_table[i] != NULL)
		{
			if (hash_table[i]->get_key() != DeletedNode<key_type, value_type>::getUniqueDeletedNode()->get_key())
			cout << "Key: " << hash_table[i]->get_key() << " " << " Student Info - " << hash_table[i]->get_value() << endl;
		}
	}
	cout << endl;
}

// Save to File function
template <class key_type, class value_type>
void HashTable<key_type, value_type>::save_to_file(ofstream & output_file)
{

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (hash_table[i] == DeletedNode<key_type, value_type>::getUniqueDeletedNode() || hash_table[i] != NULL)
		{
			if (hash_table[i]->get_key() != DeletedNode<key_type, value_type>::getUniqueDeletedNode()->get_key())
				output_file << "Key: " << hash_table[i]->get_key() << " " << " Student Info - " << hash_table[i]->get_value() << endl;
		}
	}
	output_file << endl;
}
#endif
