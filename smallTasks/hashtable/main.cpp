#include <iostream>
#include "hashtable.h"

using namespace std;

int main() {
	cout << "Hello, HashTable!" << endl;
    Hashtable <int, int> t(20);


    t.insert(1, 111);

    t.insert(12,345);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(2, 222);
    t.insert(3, 123);
    t.insert(3, 333);
    t.insert(4, 444);
    t.insert(5, 123);
    t.insert(5, 654);
    t.insert(5, 555);
    t.insert(7, 235);
    t.insert(7, 777);
    t.insert(8, 123);
    t.insert(8, 888);
    t.insert(9, 999);

    t.print();
	cout << endl << endl << endl;
    t.remove(7);

	return 0;
}
