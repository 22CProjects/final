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
	HashNode() {} // default constructor
	HashNode(key_type key, value_type value) { this->key = key; this->value = value; } // constructor with 2 constructors
	key_type get_key() { return key; } // function to return the key
	value_type get_value() { return value; } //  function to return the value of the specific key
	void set_value(value_type value) { this->value = value; } // function to set the value
};

#endif
