#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

#include "../Graph/graph.h"

template <class A, class B, class C>
class triplet {
    A first;
    B second;
    C third;
public:
    triplet(A first, B second, C third);
};

template <class A, class B, class C>
triplet <A, B, C> :: triplet(A first, B second, C third) {
    this->first = first;
    this->second = second;
    this->third = third;
}


double solveTransportTask(vector <string> cities, vector <triplet <string, string, double>> ways) {
    CountryGraph <int, int> ourGraph;
    ourGraph.insertCities(cities);
    return 0;
}

#endif
