template <typename Key, typename Value>
int Hashtable <Key, Value> :: hashFoo(Key key) {
    return key % size;
}

//CLASS HASHTABLE

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
void Hashtable <Key, Value> :: remove(Key key) {
    int ourHash = hashFoo(key);

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
void Hashtable <Key, Value> :: insert(Key key, Value value) {
    int ourHash = hashFoo(key);
    node<Key, Value>* element = new node<Key, Value>;

    element->value = value;
    element->key = key;
    element->next = data[ourHash];
    element->prev = nullptr;



    if (data[ourHash] != nullptr)
        data[ourHash]->prev = element;
    data[ourHash] = element;
}

template <typename Key, typename Value>
void Hashtable<Key, Value> :: clean() {
    for(int i = 0; i < size; ++i) {
        while(data[i] != nullptr)
            remove(data[i]->key);
    }
}

//CLASS ITERATOR
/*
template <typename Key, typename Value>
node<Key, Value>* Hashtable <Key, Value> :: Iterator :: getNode() {
    return element;
}

template <typename Key, typename Value>
Hashtable <Key, Value> :: Iterator :: Iterator() {
       element = nullptr;
   }

template <typename Key, typename Value>
Hashtable <Key, Value> :: Iterator :: Iterator(node<Key, Value>* &element) {
    this->element = element;
}

template <typename Key, typename Value>
Hashtable <Key, Value> :: Iterator :: Iterator(std::nullptr_t var) {
    this.element = var;
}

*/
