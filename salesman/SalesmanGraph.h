//
// Created by avk on 14.12.15.
//

// Algorithm from
// http://galyautdinov.ru/post/zadacha-kommivoyazhera

#ifndef SALESMAN_SALESMANGRAPH_H
#define SALESMAN_SALESMANGRAPH_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class SalesmanGraph {
    vector<vector<int>> edges;
    vector<vector<int>> estimations;
    map<string, int> toInt;
    map<int, string> toString;
    unsigned int verticesNumber;
    vector<string> vertices;
    vector <int> di, dj;
    vector<vector<int>> edgesCopy;

    vector<bool> checkedLines;
    vector<bool> checkedColumns;
public:
    SalesmanGraph();
    void insert_vertex(const string &);
    void add_edge(const string &v1, const string &v2, int weight);
    int solveTask();
    void printTable();
    void printExtendedTable();
private:
    void updateLineMinimums();
    void updateColumnMinimums();
    void performLineReduction();
    void performColumnReduction();
    void updateEstimations();
    void printEstimations();
    void removeMaxEstimation(vector<pair<int, int>>&);
};

#endif //SALESMAN_SALESMANGRAPH_H
