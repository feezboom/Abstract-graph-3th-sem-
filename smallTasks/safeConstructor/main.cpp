#include <iostream>
#include "safe.h"
#include <string>

using namespace std;

int main() {
	cout << "Hello, World!" << endl;
	try {
		A();
	}
	catch (string a) {
		cout << "Error" + a << endl;
	}
	return 0;
}
