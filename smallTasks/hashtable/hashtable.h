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
    static node<Key, Value>* getTail(node<Key, Value>* element) {
        if (element == nullptr)
            throw "invalid iterator";
        while(element->next != nullptr)
            element = element->next;
        return element;
    }
    int hashFoo(Key key);

public:
    class Iterator;

    Hashtable(int size);
    void insert(Key key, Value value);
    Value find(Key key);
    void remove(Key key);
    void clean();
    void print();
    void clear() {
        Iterator b = begin();
        Iterator e = end();

        cout << *b << "first out" << endl;
        ++b;
        cout << *b << "second out" << endl;
        ++b;
        cout << *b << "third out" << endl;

    }

    Iterator begin() {
        Hashtable <Key, Value> :: Iterator toReturn;
        node<Key, Value>* element = nullptr;
        int i = 0;
        while(element == nullptr) {
            element = data[i];
            i++;
        }
        if (data[i] == nullptr) {
            //Return end() Iterator
            return end();
        } else {
            toReturn.element = element;
            toReturn.table = this;
            return toReturn;
        }
    }
    Iterator end() {
        Hashtable<Key, Value> :: Iterator toReturn;
        toReturn.element = nullptr;
        toReturn.table = this;
        return toReturn;
    }

<<<<<<< HEAD
=======

    ~Hashtable();
};
>>>>>>> ab5e3fb947d594b3d8504ca428d8f41909b30f2b


template <typename Key, typename Value>
class Hashtable <Key, Value> :: Iterator {
private:
    //Friend classes
    friend class Hashtable <Key, Value>;
    //Fields
    node<Key, Value>* element;
    Hashtable<Key, Value>* table;
    int hash;
public:
    Iterator() {}
    Iterator(node<Key, Value>* element, Hashtable<Key, Value>* table) {
        this->element = element;
        hash = table->hashFoo(element->key);
    }

    Iterator operator++() {
        if(element == nullptr) {
            cout << "here element == nullptr(end)" << endl;
            return Iterator(nullptr, nullptr);
        }
        if(element->next != nullptr) {
            //If next isn't nullptr
            return Iterator(element->next, table);
        } else {
            //If next is nullptr
            while(1) {
                hash++;
                if(hash == table->size)
                    return Iterator(nullptr, nullptr);
                if(table->data[hash] != nullptr)
                    break;
            }
            cout << "after while [hash = " << hash << " && element = " << table->data[hash]->value << "]" << endl;

            cout << "FUCKit==";
            //If it wasn't last element it the table, but it was last in the list, return first in the next not empty list.
            Iterator it(table->data[hash], table);
            cout << it.element->key << endl;

            return it;
        }
    }
    Value operator*() {
        return this->element->value;
    }
    bool operator!=(Iterator toCompare) {
        return (this->element != toCompare.element || this->table != toCompare.table || this->hash != toCompare.hash);
    }
    ~Iterator() {}
};


#include "hashtable.hpp"
#endif
