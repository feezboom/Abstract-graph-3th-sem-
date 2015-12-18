#include "transportTestLib.h"
#include "../agraph/agraph.h"
#include "../agraph/TransportGraph.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "../jsoncpp/include/json/json.h"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

double solveOurTransportTask(string testName) {
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

    GraphFactory::makeGraph(root);
    GraphFactory::makeGraph("transport");

    vector <string> cities{"first", "second", "third", "zero", "fourth"};
    vector <way> ways;
    ways.push_back(way("first", "second", 40, Travel :: railway));
    ways.push_back(way("second", "third", 20, Travel :: road));
    ways.push_back(way("third", "fourth", 30, Travel :: railway));
    ways.push_back(way("zero", "fourth", 5, Travel :: road));
    ways.push_back(way("fourth", "second", 3, Travel :: railway));
    ways.push_back(way("third", "fourth", 6, Travel :: road));



    cout << "Transport answer: " << solveTransportTask(cities, ways) << endl;


//  Нужен тест, который провалится на жадном алгоритме.
}
