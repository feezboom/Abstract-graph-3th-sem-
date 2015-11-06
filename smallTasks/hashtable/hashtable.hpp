//CLASS HASHTABLE
template <typename Key, typename Value>
int Hashtable <Key, Value> :: hashFoo(Key key) {
    return key % size;
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

template <typename Key, typename Value>
auto& Hashtable <Key, Value> ::begin() {
	Hashtable <Key, Value> ::Iterator toReturn;
	node<Key, Value>* element = nullptr;
	int i = 0;
	while (element == nullptr && i < size) {
		element = data[i];
		i++;
	}
	if (data[i] == nullptr) {
		//Return end() Iterator
		return end();
	}
	else {
		toReturn.element = element;
		toReturn.table = this;
		toReturn.hash = hashFoo(element->key);
		return toReturn;
	}
}

template <typename Key, typename Value>
auto& Hashtable <Key, Value> ::end() {
	Hashtable<Key, Value> ::Iterator toReturn;
	toReturn.element = nullptr;
	toReturn.table = this;
	return toReturn;
}

//CLASS ITERATOR
template <typename Key, typename Value>
typename Hashtable<Key, Value> ::Iterator& Hashtable <Key, Value> ::Iterator :: operator++() {
	if (element == nullptr) {
		return table->end();
	}
	if (element->next != nullptr) {
		//If next isn't nullptr
		*this = Iterator(element->next, table);
		return *this;
	}
	else {
		//If next is nullptr
		while (1) {
			hash++;
			if (hash == table->size) {
				*this = table->end();
				return *this;
			}
			if (table->data[hash] != nullptr)
				break;
		}
		//If it wasn't last element it the table, but it was last in the list, return first in the next not empty list.
		Iterator it(table->data[hash], table);
		*this = it;
		cout << it.element->key << endl;

		return *this;
	}
}

template <typename Key, typename Value>
Hashtable<Key, Value> ::Iterator::Iterator(node<Key, Value>* element, Hashtable<Key, Value>* table) {
	this->element = element;
	this->table = table;
	if (table != nullptr)
		hash = table->hashFoo(element->key);
}

template <typename Key, typename Value>
Hashtable<Key, Value> ::Iterator::Iterator() {
	this->element = nullptr;
	this->table = nullptr;
	this->hash = -1;
}

template <typename Key, typename Value>
Value Hashtable<Key, Value> ::Iterator::operator*() {
	return this->element->value;
}

template <typename Key, typename Value>
bool Hashtable<Key, Value> ::Iterator::operator!=(Iterator toCompare) {
	return (this->element != toCompare.element || this->table != toCompare.table || this->hash != toCompare.hash);
};