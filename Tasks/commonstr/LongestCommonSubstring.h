//
// Created by avk on 15.12.15.
//

#ifndef COMMONSTR_SUFFIXARRAY_H
#define COMMONSTR_SUFFIXARRAY_H

#include <string>
#include <vector>

using namespace std;

class LongestCommonSubstring {
    vector<int> Array; // Where suffixes are sorted in lexicographical order
    vector<int> lcp; // Where LCP means "Larges Common Prefix"
    string concatenation;
    vector<int> belongs; // For each suffix contains string number, suffix belongs to(according to suffix array indexes)
    vector<string> data;
public:
    LongestCommonSubstring(string s1, string s2, string s3);
    void update(string s1, string s2, string s3);
    string toString();
    void printArrays();
private:
    string concat(string s1, string s2, string s3);

    void rebuildLCP();
    int calculateLCP_I(int pos);
    string formString(string s, int start, int finish);
    void findSuitableRange(int &left, int &right); // Suitable means that ...
    void findStartRange(int &left, int &right, int *count);
    int calculateLCPRangeMin(const int left, const int right);
    void moveRightEdge(int &left, int &right, int *count, int &max, int &suitableLeft,
                           int &suitableRight);
    void moveLeftEdge(int &left, int &right, int *count, int &max, int &suitableLeft,
                          int &suitableRight);
    string suitableStringFromSuitableRange(int left, int right);
};


#endif //COMMONSTR_SUFFIXARRAY_H
