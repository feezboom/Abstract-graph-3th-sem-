#include "transportTestLib.h"
#include "../agraph/agraph.h"
#include "../agraph/TransportGraph.h"
#include "../Tasks/transport/transport.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "../catch.hpp"
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

/*    bool res = reader.parse(ifs, root);
    if (res == false) {
        throw "mistake in json test file (" + testName + ")";
    }

    Json::Value g = root["transport"];
    cout << g << endl;
*/

    GraphFactory::makeGraph(root);

    AGraph* ourGraph = GraphFactory::makeGraph("transport");
/*
    ourGraph->insert_vertex("first");
    ourGraph->insert_vertex("second");
    ourGraph->insert_vertex("third");
    ourGraph->insert_vertex("zero");
    ourGraph->insert_vertex("fourth");

    ourGraph->add_edge("first", "second", -40);
    ourGraph->add_edge("second", "third", 20);
    ourGraph->add_edge("third", "fourth", -30);
    ourGraph->add_edge("zero", "fourth", 5);
    ourGraph->add_edge("fourth", "second", -3);
    ourGraph->add_edge("third", "fourth", 6);

    ourGraph->print_graph();
*/

    ourGraph->insert_vertex("1");
    ourGraph->insert_vertex("2");
    ourGraph->insert_vertex("3");
    ourGraph->insert_vertex("4");

    ourGraph->add_edge("1", "2", 2);
    ourGraph->add_edge("2", "4", 1000);
    ourGraph->add_edge("1", "3", 100);
    ourGraph->add_edge("3", "4", 200);

    ourGraph->print_graph();

    int answer = ourGraph->do_Dijkstra("1", "4");
    return answer;
//  Нужен тест, который провалится на жадном алгоритме.
}
