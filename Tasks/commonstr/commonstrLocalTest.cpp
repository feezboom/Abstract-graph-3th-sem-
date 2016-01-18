#include <iostream>
#include "LongestCommonSubstring.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    LongestCommonSubstring suffixArray(string("abcd"), string("bc"), string("cd"));
    cout << suffixArray.toString() << endl;
    suffixArray.printArrays();
/*
    string s1 = "banana", s2 = "ananas", s3 = "marihuana";
    suffixArray.update(s1, s2, s3);
    suffixArray.printArrays();
    cout << suffixArray.toString() << endl;
    cout << endl;*/
    return 0;
}
