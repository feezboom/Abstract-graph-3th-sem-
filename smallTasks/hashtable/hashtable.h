#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>

using namespace std;

template <typename Key, typename Value> class Hashtable;


template <typename Key, typename Value>
struct node {
    node<Key, Value>* next;
    node<Key, Value>* prev;
    Value value;
    Key key;

    void* table;
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

public:
    class Iterator;

    Hashtable(int size);
    void insert(Key key, Value value);
    Value find(Key key);
    void remove(Key key);
    void clean();
    void print();
/*
    Iterator begin() {
        node<Key, Value>* iter = nullptr;
        int i = 0;
        for(int i = 0; i < size; ++i) {
            iter = data[i];
            if (iter != nullptr)
                return Iterator(iter);
        }
        return Iterator(iter);
    }
    Iterator end() {
        node<Key, Value>* iter = nullptr;
        for(int i = size - 1; i >= 0; --i) {
            iter = data[i];
            if (iter != nullptr) {
                return Iterator(getTail(iter));
            }
        }
        return Iterator(iter);
    }
*/

    ~Hashtable();
};

template <Value>
class hashIterator {
private:

public:

};




















/*
template <typename Key, typename Value>
class Hashtable <Key, Value> :: Iterator {
private:
    friend class Hashtable <Key, Value>;
    node<Key, Value>* element;
    node<Key, Value>* getNode();
public:
    Iterator();
    Iterator(node<Key, Value>* &element);
    Iterator(std::nullptr_t var);
    Iterator operator=(Iterator it);
    Iterator operator++() {
        int size = ((Hashtable<Key, Value>*)(element->table))->size;
        node<Key, Value>** data = ((Hashtable<Key, Value>*)(element->table))->data;
        int current_pos = hashFoo(element->key, size);

        node<Key, Value>* temp = element;

        if(element == nullptr)
            return Iterator(element);

        if(element->next == nullptr && current_pos + 1 < size){
                return Iterator(data[current_pos + 1]);
        }
        element = element->next;

        return element;
    }
    Iterator operator--() {
        int size = ((Hashtable<Key, Value>*)(element->table))->size;
        node<Key, Value>** data = ((Hashtable<Key, Value>*)(element->table))->data;
        int current_pos = hashFoo(element->key, size);

        if(element == nullptr)
            return Iterator(element);

        if(element->prev == nullptr && current_pos - 1 >= 0){
                return Iterator(data[current_pos - 1]);
        }

        element = element->prev;
    }
    bool operator !=(Iterator compareTo) {
        return element != *compareTo;
    }
    bool operator == (Iterator compareTo) {
        return element == *compareTo;
    }
    bool operator !=(std::nullptr_t) {
        return element != nullptr;
    }
    bool operator ==(std::nullptr_t) {
        return element == nullptr;
    }
    Value operator*() {
        return element->value;
    }
    ~Iterator() {}
};
*/

#include "hashtable.hpp"
#endif
