#include "agraph.h"
#include <iostream>
#include <typeinfo>

#include "MainGraph.hpp"
#include "TransportGraph.h"
#include "LandingGraph.h"


AGraph* GraphFactory::makeGraph(string& name, Json::Value& graph){
    if(name == "transport") {
        return nullptr;
    }
    if(name == "landing") {
        return nullptr;
    }
}
