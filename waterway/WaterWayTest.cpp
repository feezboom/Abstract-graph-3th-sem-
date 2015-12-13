#include <iostream>
#include "FenwickTree.h"

using namespace std;

int main() {
    cout << "Hello, Waterway!" << endl;

    vector<double> ourMas = {1,3,4,8,4,3,4,5,6,7,3,4,6,1,2,4,0,7,6,4,7,8};
    FenwickTree fenwickTree(ourMas);
    return 0;
}