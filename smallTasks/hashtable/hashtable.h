#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
#include <stdio.h>

using namespace std;

template <typename Key, typename Value> class Hashtable;

template <typename Key, typename Value>
struct node {
    node<Key, Value>* next;
    node<Key, Value>* prev;
    Value value;
    Key key;
};

template <typename Key, typename Value>
class Hashtable {
private:
	int size;
	node<Key, Value>** data;
	int hashFoo(Key key);

public:
	class Iterator;
	Hashtable(int size);
	void insert(Key key, Value value);
	Value find(Key key);
	void remove(Key key);
	void clean();
	void print();

	auto& begin();
	auto& end();
};

template <typename Key, typename Value>
class Hashtable <Key, Value> :: Iterator {
private:
    //Fields
    node<Key, Value>* element;
    Hashtable<Key, Value>* table;
    int hash;
public:
	Iterator();
	Iterator(node<Key, Value>* element, Hashtable<Key, Value>* table);

	Iterator& operator++();
	Value operator*();
	bool operator!=(Iterator toCompare);
    ~Iterator() {}
};

#include "hashtable.hpp"
#endif
