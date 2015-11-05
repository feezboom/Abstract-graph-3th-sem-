#include <iostream>
#include "hashtable.h"

using namespace std;

int main() {
	cout << "Hello, HashTable!" << endl;
    Hashtable <int, int> t(20);

    t.insert(1, 123);
    t.insert(1, 223);
    t.insert(1, 323);
    t.insert(1, 423);
    t.insert(1, 523);

    t.insert(12,345);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(2, 123);
    t.insert(3, 123);
    t.insert(3, 123);
    t.insert(4, 123);
    t.insert(5, 123);
    t.insert(5, 654);
    t.insert(5, 123);
    t.insert(7, 235);
    t.insert(7, 123);
    t.insert(8, 123);
    t.insert(8, 564);
    t.insert(9, 154);
    t.insert(0, 123);

    t.print();

    t.remove(7);

    t.clean();

    t.print();

	return 0;
}
