#ifndef _SAFE_H_
#define _SAFE_H_

using namespace std;

class A;
class B;
class C;

class A {
	int* b;
	double* c;
public:
	A() {
		b = new int[100];
		if (b == nullptr)
			throw "error allocating";

		c = new double[100];
		if (c == nullptr) {
			delete[] b;
			throw "error allocating";
		}
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

#endif // _SAFE_H_
