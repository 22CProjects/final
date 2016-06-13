#ifndef HASTTABLE_H
#define HASTTABLE_H

#include <stdio.h>     
#include <stdlib.h>   
#include <time.h>
#include "HashNode.h"
#include "DeletedNode.h"

const int HASH_TABLE_SIZE = 40;

template <class value_type, class key_type>
class HashTable
{
private:
	HashNode<value_type, key_type> ** hash_table;
	int pseudo_array[HASH_TABLE_SIZE];

public:
	HashTable();
	~HashTable();
	void insert(key_type key, value_type value);
	int find(key_type key);
	void remove(key_type key);
	void print_table();
};

template <class value_type, class key_type>
HashTable<value_type, key_type>::HashTable()
{
	hash_table = new HashNode<value_type, key_type>*[HASH_TABLE_SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		hash_table[i] = NULL;
		int x = rand() % 30;
		pseudo_array[i] = x;
	}

}

template <class value_type, class key_type>
HashTable<value_type, key_type>::~HashTable()
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (hash_table[i] != NULL && hash_table[i] != DeletedNode<value_type, key_type>::getUniqueDeletedNode())
		{
			delete hash_table[i];
		}
	}

	delete[] hash_table;
}

template <class value_type, class key_type>
void HashTable<value_type, key_type>::insert(key_type key, value_type value)
{
	int hash_key = (key % HASH_TABLE_SIZE);
	int first_hash = -1;
	int deleted_node = -1;
	int counter = 0;

	while (hash_key != first_hash && (hash_table[hash_key] == DeletedNode<value_type, key_type>::getUniqueDeletedNode() || hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() != key))
	{
		if (first_hash == -1)
		{
			first_hash = hash_key;
		}

		if (hash_table[hash_key] == DeletedNode<value_type, key_type>::getUniqueDeletedNode())
		{
			deleted_node = hash_key;
		}

		counter++;
		hash_key = (hash_key + pseudo_array[counter]) % HASH_TABLE_SIZE;
	}

	if ((hash_table[hash_key] == NULL || hash_key == first_hash) && deleted_node != -1)
	{
		hash_table[deleted_node] = new HashNode<value_type, key_type>(key, value);
	}
	else if (first_hash != hash_key)
	{
		if (hash_table[hash_key] != DeletedNode<value_type, key_type>::getUniqueDeletedNode() && hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() == key)
		{
			hash_table[hash_key]->set_value(value);
		}
		else
		{
			hash_table[hash_key] = new HashNode<value_type, key_type>(key, value);
		}
	}
}

template <class value_type, class key_type>
int HashTable<value_type, key_type>::find(key_type key)
{
	int hash_key = (key % HASH_TABLE_SIZE);
	int first_hash = -1;
	int counter = 0;
	while (hash_key != first_hash && (hash_table[hash_key] == DeletedNode<value_type, key_type>::getUniqueDeletedNode() || hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() != key))
	{
		if (first_hash == -1)
		{
			first_hash = hash_key;
		}

		counter++;
		hash_key = (hash_key + pseudo_array[counter]) % HASH_TABLE_SIZE;;
	}
	if (hash_table[hash_key] == NULL || hash_key == first_hash)
	{
		return -1;
	}
	else
	{
		return hash_table[hash_key]->get_value();
	}
}

template <class value_type, class key_type>
void HashTable<value_type, key_type>::remove(key_type key)
{
	int hash_key = (key % HASH_TABLE_SIZE);
	int first_hash = -1;
	int counter = 0;

	while (hash_key != first_hash && (hash_table[hash_key] == DeletedNode<value_type, key_type>::getUniqueDeletedNode() || hash_table[hash_key] != NULL && hash_table[hash_key]->get_key() != key)) {
		if (first_hash == -1)
		{
			first_hash = hash_key;
		}

		counter++;
		hash_key = (hash_key + pseudo_array[counter]) % HASH_TABLE_SIZE;;
	}
	if (hash_key != first_hash && hash_table[hash_key] != NULL)
	{
		delete hash_table[hash_key];
		hash_table[hash_key] = DeletedNode<value_type, key_type>::getUniqueDeletedNode();
	}
}

template <class value_type, class key_type>
void HashTable<value_type, key_type>::print_table()
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (hash_table[i] == DeletedNode<value_type, key_type>::getUniqueDeletedNode() || hash_table[i] != NULL)
		{
			cout << "Key: " << hash_table[i]->get_key() << " " << " Value: " << hash_table[i]->get_value() << endl;
		}
	}
	cout << endl;
}
#endif