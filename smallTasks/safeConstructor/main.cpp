#include <iostream>
#include "safe.h"
#include <string>

using namespace std;

int main() {
	cout << "Hello, World!" << endl;
	try {
		A(10, 11);
	}
	catch (string a) {
		cout << "Error" + a << endl;
	}

	try {
		A(10, -9);
	}
	catch (string a) {
		cout << "Error" + a << endl;
	}
	try {
		A(0, 11);
	}
	catch (string a) {
		cout << "Error" + a << endl;
	}
	try {
		A(-7, -8);
	}
	catch (string a) {
		cout << "Error" + a << endl;
	}

	return 0;
}
