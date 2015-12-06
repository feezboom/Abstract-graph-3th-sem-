#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

#include <string>
#include "../agraph/agraph.h"
#include "../agraph/TransportGraph.h"

struct way {
    string a;
    string b;
    double price;
    Travel travelType;
    way(string a, string b, double Price, Travel type);
};
way :: way(string a, string b, double Price, Travel type) {
    this->a = a;
    this->b = b;
    this->price = Price;
    this->travelType = type;
}


int solveTransport(AGraph* graph) {

}

double solveTransportTask(vector <string> cities, vector <way> ways) {
    CountryGraph <int, int> ourGraph;
    ourGraph.insertCities(cities);
    for(const auto& way : ways) {
        try {
            way.travelType == Travel :: railway ? ourGraph.addRailway(way.a, way.b, way.price) : ourGraph.addRoad(way.a, way.b, way.price);
        }
        catch (string error) {
            cout << "insertion error : " << error << endl;
        }
    }
    //It was only filling

    //Then we're going to do ... what???

    cout << "The cheapest way is " << ourGraph.findTheCheapestWay("second", "first") << endl;

    ourGraph.printCountry();

    return 0;
}

#endif
