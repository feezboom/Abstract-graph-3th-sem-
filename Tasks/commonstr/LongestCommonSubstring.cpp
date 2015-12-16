//
// Created by avk on 15.12.15.
//

#include "LongestCommonSubstring.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <limits.h>

using namespace std;

LongestCommonSubstring::LongestCommonSubstring(string s1, string s2, string s3) {
    update(s1, s2, s3);
}

void LongestCommonSubstring::update(string s1, string s2, string s3) {
    // Getting string to make suffix array from
    string temp = concatenation = concat(s1, s2, s3);
    if ((int)concatenation.find("#$") != -1 ||
            (int)concatenation.find("$&") != -1 ||
            (int)concatenation.find("#&") != -1)
        return;

    // Initialization
    unsigned long size = concatenation.size();
    Array.resize(size, 0);
    belongs.resize(size, 0);
    data.resize(size, "");

    // Filling data && A(suffix array) arrays
    data[0] = temp;
    for (int i = 1; i < size; ++i) {
        data[i] = temp.erase(0, 1);
        Array[i] = i;
    }

    // Sorting data && A(suffix array) arrays
    for (int i = 0; i < size - 1; ++i)
        for (int j = i; j < size; ++j)
            if (data[i] > data[j]) {
                swap(data[i], data[j]);
                swap(Array[i], Array[j]);
            }

    // Filling belongs array
    for (int i = 0; i < size; ++i) {
        // If fisrt separator
        if (data[i][0] == '#' || data[i][0] == '$' || data[i][0] == '&')
            belongs[i] = -1;
        else {
            if ((int) data[i].find("#") != -1)
                // First string
                belongs[i] = 0;
                // else if second separator
            else if ((int) data[i].find("$") != -1)
                // Second string
                belongs[i] = 1;
                // else (if (no first && no second) separators)
            else
                // Third string
                belongs[i] = 2;
        }
    }

    // Here we have sorted array of each suffix of our input string
}

string LongestCommonSubstring::concat(string s1, string s2, string s3) {
    return string(s1 +  "#" + s2 + "$" + s3 + "&");
}

void LongestCommonSubstring::rebuildLCP() {
    lcp.resize(concatenation.size(), 0);
    for (int i = 1; i < concatenation.size(); ++i) {
        lcp[i] = calculateLCP_I(i);
    }
}

int LongestCommonSubstring::calculateLCP_I(int pos) {
    assert(pos >= 1 && pos < concatenation.size());
    int i = 0;
    string suffix1 = formString(concatenation, Array[pos], (int) concatenation.size() - 1);
    string suffix2 = formString(concatenation, Array[pos - 1], (int) concatenation.size() - 1);
    while(suffix1[i] == suffix2[i]) i++;
    return i;
}

string LongestCommonSubstring::formString(string s, int start, int finish) {
    assert(start < s.size() && start >= 0);
    assert(finish < s.size() && finish >= 0);
    assert(start <= finish);
    if (finish != s.size() - 1)
        s.erase((unsigned long) finish + 1, s.size() - (finish + 1));
    s.erase(0, (unsigned long) start);
    return s;
}

void LongestCommonSubstring::findSuitableRange(int &left, int &right) {
    int count[3]; // The quantity of each string in the current range
    findStartRange(left, right, count);
    assert(count[0] != 0 && count[1] != 0 && count[2] != 0); // Check if count is OK!
    int max = calculateLCPRangeMin(left, right);
    int suitableLeft = left, suitableRight = right;
    // Here we have start range
    while((right < Array.size() - 1) && left < Array.size()) {
        // MOVING LEFT EDGE
        moveLeftEdge(left, right, count, max, suitableLeft, suitableRight);
        moveRightEdge(left, right, count, max, suitableLeft, suitableRight);
        //Here we've found next suitable range candidate
        assert(suitableLeft <= suitableRight);
    }
    left = suitableLeft;
    right = suitableRight;
}

void LongestCommonSubstring::moveLeftEdge(int &left, int &right, int *count, int &max, int &suitableLeft,
                                          int &suitableRight) {
    while (count[0] != 0 && count[1] != 0 && count[2] != 0) {

        int candidate = calculateLCPRangeMin(left, right);
        if (max < candidate) {
            max = candidate;
            suitableLeft = left;
            suitableRight = right;
        }

        // Trying to except
        if(belongs[left] != -1)
            count[belongs[left]]--;
        // moving left edge
        left++;
        // Checking if all right.
        // If all right, move left edge again.
        // Do it until count[0] == 0 || count[1] == 0 || count[2] == 0
    }

}
void LongestCommonSubstring::moveRightEdge(int &left, int &right, int *count, int &max, int &suitableLeft,
                                           int &suitableRight) {
    while ((count[0] == 0 || count[1] == 0 || count[2] == 0) && right < Array.size() - 1) {
        // move right edge
        right++;
        // Ignoring separators we
        // update count array
        if (belongs[right] != -1)
            // Belongs[right] == -1 means that suffix number 'right' begins with separator
            // We ignore such suffix
            count[belongs[right]]++;
        // Checking if all right.
        // If all right, move right edge again.
        // Do it until count[0] == 0 || count[1] == 0 || count[2] == 0
    }
    int candidate = calculateLCPRangeMin(left, right);
    if (max < candidate) {
        max = candidate;
        suitableLeft = left;
        suitableRight = right;
    }
}

void LongestCommonSubstring::findStartRange(int &left, int &right, int *count) {
    left = right = 0;
    count[0] = count[1] = count[2] = 0;
    if(belongs[left] != -1)
        count[belongs[left]]++;
    while(count[0] == 0 || count [1] == 0 || count[2] == 0) {
        right++;
        if (belongs[right] != -1)
            count[belongs[right]]++;
    }
//    cout << "start range is " << left << " " << right <<  endl;
//    fillCountArrayInRange(left, right, count);
    assert(count[0] != 0 && count[1] != 0 && count[2] != 0);
    return;
}

int LongestCommonSubstring::calculateLCPRangeMin(int left, int right) {
    assert(left < right);
    left++;
    int min = INT_MAX;
    for (int i = left; i <= right; ++i) {
        min = (lcp[i] < min) ? lcp[i] : min;
    }
    return min;
}

string LongestCommonSubstring::suitableStringFromSuitableRange(int left, int right) {
    assert(left < right);
    assert(left >= 0);
    assert(right > 0);
    int rangeMin = calculateLCPRangeMin(left, right);
    int suitableSuffix = -1;
    int suffixLength = -1;

    for (int i = left + 1; i <= right; ++i) {
        if (lcp[i] == rangeMin) {
            suitableSuffix = Array[i];
            suffixLength = lcp[i];
            break;
        }
    }
    assert(suitableSuffix != -1 && suffixLength != -1);
    assert(suitableSuffix + suffixLength - 1 < concatenation.size());

    return formString(concatenation, suitableSuffix, suitableSuffix + suffixLength - 1);
    
}

string LongestCommonSubstring::toString() {
    if (    (int)concatenation.find("#$") != -1 ||
            (int)concatenation.find("$&") != -1 ||
            (int)concatenation.find("#&") != -1)
        return string("");
    rebuildLCP();
    int left, right;
    findSuitableRange(left, right);
//        cout << "x = " << left << " y = " << right << endl;
//        cout << "string = " << suitableStringFromSuitableRange(left, right);
    return suitableStringFromSuitableRange(left, right);

}

void LongestCommonSubstring::printArrays() {
    // Printing A && data arrays
    rebuildLCP();
    unsigned long size = data.size();
    for (int i = 0; i < size; ++i) {
        cout.width(2);
        if (i != 0)
            cout << lcp[i] << "|";
        else
            cout << "-" << "|";
        cout.width(2);
        cout << i << "|";
        cout.width(2);
        cout << Array[i] << " " << data[i] << " " << " | belongs to ";
        cout << belongs[i] << endl;
    }
    cout << endl;
}
