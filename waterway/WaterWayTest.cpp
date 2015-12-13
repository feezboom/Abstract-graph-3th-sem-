#include <iostream>
#include "FenwickTree.h"

using namespace std;

int main() {
    cout << "Hello, Waterway!" << endl;
    vector<vector<int>> ourMas = {  vector<int>{1,2,3},
                                    vector<int>{4,6,5},
                                    vector<int>{7,8,9} };
    FenwickTree fenwickTree(ourMas);

    cout << "AnswerIs->" << fenwickTree.getMax(2,3,1,2) << endl;
    return 0;
}