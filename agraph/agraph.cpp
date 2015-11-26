#include "agraph.h"
#include <iostream>
#include <typeinfo>

#include "MainGraph.h"
#include "TransportGraph.h"
#include "LandingGraph.h"


AGraph* GraphFactory::makeGraph(string& name){
    if(name == "transport") {
        return new AGraph(CountryGraph <int, int>());
    }
    if(name == "landing") {
        return new AGraph(LandingGraph());
    }
}


AGraph* GraphFactory::makeGraph() {
    return nullptr;
}
