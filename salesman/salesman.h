#ifndef _SALESMAN_H_
#define _SALESMAN_H_

#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include "../jsoncpp/include/json/json.h"
#include "../../agraph/agraph.h"

using std::string;

//Working with tests
void findSalesmanTest(string name, std :: ifstream& ifs) {
    ifs.open("../salesman/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../ninja_turtles/salesman/tests/" + name, std::ifstream::in);
    if(!ifs)
    ifs.open("../../salesman/tests/" + name, std::ifstream::in);
    if(!ifs)
        throw "test file " + name + " was not found";
}

int testSalesman(string testPath) {
    std::ifstream ifs;
    Json::Value root;
    Json::Reader reader;
    ifs.open(testPath, std::ifstream::in);
    bool res = reader.parse(ifs, root);

    Json::Value data = root["salesman"];

    string name("salesman");
    AGraph* myGraph = GraphFactory :: makeGraph(name);



    return 234;
}


#endif
