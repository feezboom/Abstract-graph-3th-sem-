#include <vector>
#include "jsoncpp/include/json/json.h"
#include "agraph/agraph.h"

#include "Tasks/commonstr/LongestCommonSubstring.h"

#include "catch.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


SCENARIO("ZERO") {
    cout << "Initialized" << endl;
}

SCENARIO("Testing largest common substring of 3 strings") {
    GIVEN("first test, suffix array class, 3 strings") {
        string s1, s2, s3;
        LongestCommonSubstring suffixArray("", "", "");
        WHEN("string are banana, ananas, marihuana") {
            s1 = "banana"; s2 = "ananas"; s3 = "marihuana";
            suffixArray.update(s1, s2, s3);
            REQUIRE(suffixArray.toString() == "ana");
        }
        WHEN("string are abracadabra, radar, abraradam") {
            s1 = "abracadabra"; s2 = "radar"; s3 = "abraradam";
            suffixArray.update(s1, s2, s3);
            REQUIRE(suffixArray.toString() == "ada");
        }
        WHEN("strings are the same") {
            s1 = "hello"; s2 = "hello", s3 = "hello";
            suffixArray.update(s1, s2, s3);
            REQUIRE(suffixArray.toString() == "hello");
        }
        WHEN("strings are empty") {
            s1 = ""; s2 = "", s3 = "";
            suffixArray.update(s1, s2, s3);
            REQUIRE(suffixArray.toString() == "");
        }
        WHEN("one or two strings are empty") {
            s1 = ""; s2 = "www", s3 = "qq";
            suffixArray.update(s1, s2, s3);
            REQUIRE(suffixArray.toString() == "");
            s1 = ""; s2 = "s"; s3 = "";
            suffixArray.update(s1, s2, s3);
            REQUIRE(suffixArray.toString() == "");
        }
    }
}
