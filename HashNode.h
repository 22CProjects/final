// Node header file 
#ifndef HASHNODE_H
#define HASHNODE_H

#include <iostream>
#include <string>

using namespace std;

template <class value_type, class key_type>
class HashNode
{
private:
	key_type key;
	value_type value;

public:
	HashNode() {}
	HashNode(key_type key, value_type value) { this->key = key; this->value = value; }
	int get_key() { return key; }
	value_type get_value() { return value; }
	void set_value(value_type value) { this->value = value; }
};

#endif