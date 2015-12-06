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

int solveSalesman(AGraph* graph) {

    return 234;
}


#endif
