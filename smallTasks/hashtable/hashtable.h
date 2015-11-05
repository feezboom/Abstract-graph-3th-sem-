#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>

using namespace std;

template <typename Key, typename Value> class Hashtable;

template <typename Key>
static int hashFoo(Key key, int size) {
    return key % size;
}
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

    Iterator begin() {
        node<Key, Value>* iter = nullptr;
        int i = 0;
        for(int i = 0; i < size; ++i) {
            iter = data[i];
            cout << "BEE HERE" << endl;
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

    ~Hashtable();
};

template <typename Key, typename Value>
void Hashtable<Key, Value> :: clean() {
    for(Iterator it = begin(); it != nullptr; ++it) {
        auto q = it.getNode();
        cout << "PRINTITNGNODES: ";
        while(q != nullptr) {
            cout << q->value << "->";
            q = q->next;
        }
        cout << "nullptr" << endl;

        delete it.getNode();
    }
}

template <typename Key, typename Value>
void Hashtable <Key, Value> :: print() {
    cout << "You called printing hashtable. Now we're starting" << endl;
    cout << "Printing format ${hash} -> {value} --> {value} --> ..." << endl;
    for (int i = 0; i < size; ++i) {
        cout << i << "-->>";
        node<Key, Value>* iter = data[i];
        while(iter != nullptr) {
            cout << "{" << iter->value << "}" << "-->";
            iter = iter->next;
        }
        cout << "nullptr" << endl;

    }
}

template <typename Key, typename Value>
void Hashtable <Key, Value> :: insert(Key key, Value value) {
    int ourHash = hashFoo(key, size);
    node<Key, Value>* element = new node<Key, Value>;

    element->table = this;
    element->value = value;
    element->key = key;
    element->next = data[ourHash];
    element->prev = nullptr;



    if (data[ourHash] != nullptr)
        data[ourHash]->prev = element;
    data[ourHash] = element;
}

template <typename Key, typename Value>
void Hashtable <Key, Value> :: remove(Key key) {
    int ourHash = hashFoo(key, size);

    node<Key, Value>* iter = data[ourHash];
    while(iter != nullptr) {
        if (iter->key == key) {
            if (iter->next != nullptr)
                iter->next->prev = iter->prev;

            if (iter->prev != nullptr)
                iter->prev->next = iter->next;
            else
                data[ourHash] = iter->next;

            delete iter;
            cout << "Succesfully deleted" << endl;
            return;
        }
    }
    cout << "There is no such element in hashtable. Cannot delete it." << endl;
}

template <typename Key, typename Value>
Hashtable <Key, Value> :: Hashtable(int size) {
    if (size == 0)
        throw "Hash table can not be zero sized.";
    //Table size
    this->size = size;

    //Table data
    data = new node<Key, Value>*[size];

    for(int i = 0; i < size; ++i) {
        data[i] = nullptr;
    }
}

template <typename Key, typename Value>
Hashtable <Key, Value> :: ~Hashtable() {

}

template <typename Key, typename Value>
Value Hashtable <Key, Value> :: find(Key key) {
    int ourHash = hashFoo(key);
    node<Key, Value>* iter = data[ourHash];
    while(iter != nullptr) {
        if (iter->key == key) {
            return iter->value;
        }
    }
    cout << "Required element was not found. Maybe you made a typo?" << endl;
}

template <typename Key, typename Value>
class Hashtable <Key, Value> :: Iterator {
private:
    friend class Hashtable <Key, Value>;
    node<Key, Value>* element;
    node<Key, Value>* getNode() {
        return element;
    }
public:
    Iterator() {
        element = nullptr;
    }
    Iterator(node<Key, Value>* &element) {
        this->element = element;
    }
    Iterator(std::nullptr_t var) {
        this.element = var;
    }

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



#endif
