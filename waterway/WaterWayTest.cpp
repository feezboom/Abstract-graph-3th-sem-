#include <iostream>
#include "FenwickTree.h"

using namespace std;

int main() {
    cout << "Hello, Waterway!" << endl;

    vector<double> ourMas = {1,3,4,4,3,4,5,6,7,3,9,4,6,1,2,4,0,7,6,4,7,9,8};
    FenwickTree fenwickTree(ourMas);

    cout << fenwickTree.getMax(1,15) << endl;
    return 0;
}