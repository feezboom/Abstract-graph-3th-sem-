#include <iostream>
#include "FenwickTree.h"

using namespace std;

int main() {
    cout << "Hello, Waterway!" << endl;
    vector<vector<int>> ourMas = {  vector<int>{ 3,  6,   1, 0, 7},
                                    vector<int>{-1, 10, 100, 6, 1},
                                    vector<int>{ 4,  5, -10, 3, 9} };
    FenwickTree fenwickTree(ourMas);

    cout << "AnswerIs->" << fenwickTree.getMin(4,4,1,3) << endl;
    return 0;
}
