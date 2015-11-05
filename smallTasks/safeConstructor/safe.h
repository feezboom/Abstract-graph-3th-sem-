#ifndef _SAFE_H_
#define _SAFE_H_

#include <string>
using namespace std;

class A;
class B;
class C;

class A {
	int* b;
	double* c;
public:
	A(int x, int y) {
		if (x <= 0/*some condition*/)
			throw string("X can not be below or equal zero");
		b = new int[100];
		if (y <= 0/*some condition*/) {
			delete[] b;
			throw string("Y can not be below or equal zero");
		}
		c = new double[100];

		cout << "Constructor succeded" << endl;
	}
	~A() {
		delete[] b;
		delete[] c;
	}	
};

class B {
	int b;
};
class C {
	int c;
};

#endif
