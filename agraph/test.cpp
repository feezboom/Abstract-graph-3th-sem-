#include <iostream>
#include "agraph.h"
#include "graphs_export.h"
#include "TransportGraph.h"
#include "../jsoncpp/include/json/json.h"
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
    std::cout << "Hello, agraph!" << std :: endl;


    vector <string> cities{"Moscow", "Nyagan", "Surgut", "Khanty-Mansiysk", "Nizhnevartovsk"};
    CountryGraph <int, int> ourGraph;
    ourGraph.insertCities(cities);
    cout << "The cheapest way is " << ourGraph.findTheCheapestWay("second", "first") << endl;
    ourGraph.printCountry();



    return 0;
}
