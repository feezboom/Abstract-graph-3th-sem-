#include "agraph.h"
#include <iostream>
#include <typeinfo>

#include "MainGraph.hpp"
#include "TransportGraph.h"
#include "LandingGraph.h"


string getTaskName(Json::Value root) {
    if (root["salesman"] != Json::Value::null)
        return "salesman";
    else if (root["2sat"] != Json::Value::null)
        return "2sat";
    else  if (root["landing"] != Json::Value::null)
        return "landing";
    else
        return "null";
}

AGraph* GraphFactory::makeGraph(string& name, Json::Value& graph){
    if(name == "transport") {
        return nullptr;
    }
    if(name == "landing") {
        return nullptr;
    }
}
