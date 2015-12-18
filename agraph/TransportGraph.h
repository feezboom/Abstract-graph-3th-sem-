#ifndef _TRANSPORTGRAPH_H_
#define _TRANSPORTGRAPH_H_

#include "MainGraph.hpp"
#include <assert.h>

//*******************************************TRANSPORT BEGIN**************************************************//
enum class Travel {
    road, railway, bus, train, car, plane, ship, byFoot, nohow
};
template <class type>
class City : public vertex<type> {
private:
    template <class V, class U>
    friend class CountryGraph;

    unordered_map <string, shared_ptr <City <type>>> roads_to;
    unordered_map <string, shared_ptr <City <type>>> roads_from;

    unordered_map <string, shared_ptr <City <type>>> railways_to;
    unordered_map <string, shared_ptr <City <type>>> railways_from;

    Travel previousTravel;

    void addRoadTo(string name, shared_ptr <City<type>> pointer);
    void addRoadFrom(string name, shared_ptr <City<type>> pointer);
    void addRailwayTo(string name, shared_ptr <City<type>> pointer);
    void addRailwayFrom(string name, shared_ptr <City<type>> pointer);
public:
    City();
    City(const string& name);
    void printCity();
    void printRoads();
    void printRailways();
};
template <class type, class E>
class CountryGraph : public graph_list <type, E> {
private:
    const size_t discount = 20; //Our discount when we change type of transport in percents
    const double applyDiscount = 1 - (double)discount/100;

    list <shared_ptr <City <type>>> cityList;
    map <string, map <string, double>> roadsPrice;
    map <string, map <string, double>> railwaysPrice;

    void whitewashAll();
    void makeDistancesInfinite();
    bool areAllBlack();
    bool cityInCountry(const string& name);
    shared_ptr <City<type>> getPtr(const string& name);

public:
    // Для концепта
    virtual void insert_vertex(const string &name) {
        insertCity(name);
    }
    virtual void print_graph() {
        printCountry();
    }
    virtual void add_edge(string from, string to, double weight = 0) {
        assert(weight != 0);
        if (weight > 0)
            addRoad(from, to, weight);
        if (weight < 0)
            addRailway(from, to, -weight);
    }
    virtual vector<vector<string>> getStrongComponents() {
        // Метод не нужен
        return vector<vector<string>>();
    }
    virtual double do_Dijkstra(string from, string to);
    // Для концепта

    void insertCity(const string &cityName);
    void insertCities(const vector <string> &cities);
    void addRoad(const string &city1, const string &city2, double price);
    void addRailway(const string &city1, const string &city2, double price);
    double findTheCheapestWay(const string &start, const string &finish);
    void theCheapesWayUpdate();
    shared_ptr <City<type>> findMinDistanceCity();
    void processing();//searchingTheCheapestWay
    void printCountry();
};
//*******************************************TRANSPORT END****************************************************//

#include "TransportGraph.hpp"

#endif
