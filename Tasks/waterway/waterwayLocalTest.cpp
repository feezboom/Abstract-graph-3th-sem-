#include <iostream>
#include "FenwickTree.h"

using namespace std;

int main() {
    cout << "Hello, Waterway!" << endl;
    vector<vector<int>> ourMas = {  vector<int>{-5,  6,   1, -15, 7},
                                    vector<int>{19, 10, 100, 6, 1},
                                    vector<int>{40,  5, -10, 3, 9} };
    FenwickTree fenwickTree(ourMas);

    cout << "AnswerIs->" << fenwickTree.getMin(1,3,1,3) << endl;
    cout << "AnswerIs->" << fenwickTree.getMin(1,5,1,1) << endl;



    cout << FenwickTree::G(1);

    return 0;
}
