#include "transportTestLib.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "../jsoncpp/include/json/json.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

double solveTransportTask(string testName) {
    ifstream ifs;
    Json::Value root;
    Json::Reader reader;

    findTest("transport", testName, ifs);

    assert(ifs);

    bool res = reader.parse(ifs, root);
/*    if (res == false) {
        throw "mistake in json test file (" + testName + ")";
    }

    Json::Value g = root["transport"];
    cout << g << endl;
*/



}
