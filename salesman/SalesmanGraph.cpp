//
// Created by avk on 14.12.15.
//

#include "SalesmanGraph.h"
#include <iostream>
#include <limits.h>

using namespace std;

SalesmanGraph::SalesmanGraph() {
    verticesNumber = 0;
}
void SalesmanGraph::insert_vertex(const string &input) {
    toInt[input] = verticesNumber;
    toString[verticesNumber] = input;

    vertices.push_back(input);

    verticesNumber++;

    di.resize(verticesNumber, INT_MAX);
    dj.resize(verticesNumber, INT_MAX);


    edges.resize(verticesNumber, vector<int>());
    estimations.resize(verticesNumber, vector<int>());
    edgesCopy.resize(verticesNumber, vector<int>());

    for(vector<int> &it : edges)
        it.resize(verticesNumber, INT_MAX);
    for(vector<int> &it : estimations)
        it.resize(verticesNumber, INT_MAX);
    for(vector<int> &it : edgesCopy)
        it.resize(verticesNumber, INT_MAX);

}
void SalesmanGraph::add_edge(const string &v1, const string &v2, int weight) {
    edges[toInt[v1]][toInt[v2]] = weight;
    edgesCopy[toInt[v1]][toInt[v2]] = weight;
}

void SalesmanGraph::printTable() {
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            cout.width(12);
            cout << edges[i][j];
        }
        cout << endl;
    }
}

void SalesmanGraph::printExtendedTable() {
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            cout.width(12);
            cout << edges[i][j];
        }
        cout.width(20);
        cout << di[i];
        cout << endl;
    }
    cout << endl << endl;
    for (const auto &it: dj) {
        cout.width(12);
        cout << it;
    }
    cout << endl << "</end>" << endl;
}

int SalesmanGraph::solveTask() {
    vector<pair<int, int>> answer;
    unsigned long size = edges.size();

    checkedLines = vector<bool> (edges.size(), false);
    checkedColumns = vector<bool> (edges[0].size(), false);

    while (size-- > 1) {
        updateLineMinimums();
        performLineReduction();
        updateColumnMinimums();
        performColumnReduction();
        updateEstimations();
        removeMaxEstimation(answer);
    }
    // And let's find the last :)
    int y, x;
    // Let's first find line:
    for (int i = 0; i < edges.size(); ++i)
        if (checkedLines[i] == false) { y = i; break; }
    for (int i = 0; i < edges[0].size(); ++i)
        if(checkedColumns[i] == false) { x = i; break; }
    // We've found it!
    answer.push_back(make_pair(y,x));
    // Got it!

    // Now let's make way
    vector<int> way; way.push_back(answer[0].first);
    vector<bool> used(edges.size(), false);
    bool finish = false;
    int activeIndex = 0;
    while (!finish) {
        finish = true;
        for (int i = 0; i < answer.size(); ++i) {
            if(answer[activeIndex].second == answer[i].first && !used[i]) {
                used[i] = true;
                way.push_back(answer[activeIndex].second);
                activeIndex = i;
                finish = false;
            }
        }
    }
    // And it is ready too;
    // Then, let's calculate way cost
    int sum = 0;
    for (int i = 0; i < way.size() - 1; ++i)
        sum += edgesCopy[way[i]][way[i+1]];
    return sum;
}

void SalesmanGraph::updateLineMinimums() {
    // Now let's find min in each line
    // of table
    for(int i = 0; i < edges.size(); ++i) {
        int min = INT_MAX;
        for(const auto &jt : edges[i]) {
            min = (jt < min) ? jt : min;
        }
        di[i] = min;
    }
}

void SalesmanGraph::updateColumnMinimums() {
    for (int i = 0; i < edges[0].size(); ++i) {
        int min = INT_MAX;
        for (const auto &j : edges) {
            min = (min < j[i]) ? min : j[i];
        }
        dj[i] = min;
    }
}

void SalesmanGraph::performLineReduction() {
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            edges[i][j] -= di[i];
        }
    }
}

void SalesmanGraph::performColumnReduction() {
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            edges[i][j] -= dj[j];
        }
    }
}

void SalesmanGraph::updateEstimations() {
    for (int i = 0; i < edges.size(); ++i)
        for (int j = 0; j < edges[i].size(); ++j)
            if((edges[i][j] == 0)) {
                // Then we'll see min in i line and j column
                int minLine = INT_MAX;
                int minColumn = INT_MAX;
                for (int k = 0; k < edges[i].size(); ++k)
                    if (k != j) minLine = (minLine < edges[i][k] ? minLine : edges[i][k]); // Line
                for (int k = 0; k < edges.size(); ++k)
                    if (k != i) minColumn = (minColumn < edges[k][j]) ? minColumn : edges[k][j]; // Column
                estimations[i][j] = minLine + minColumn; // Estimation
            }

}

void SalesmanGraph::printEstimations() {
    for(const auto &it : estimations) {
        for(const auto &jt : it) {
            cout.width(12);
            cout << jt;
        }
        cout << endl;
    }
}

void SalesmanGraph::removeMaxEstimation(vector<pair<int, int>> &answer) {
    int x = 0, y = 0;
    int max = -INT_MAX;
    for (int i = 0; i < edges.size(); ++i) {
        for (int j = 0; j < edges[i].size(); ++j) {
            if(edges[i][j] == 0 && estimations[i][j] > max && !checkedColumns[j] && !checkedLines[i]) {
                max = estimations[i][j];
                y = i;
                x = j;
            }
        }
    }
    // Max estimation is found - it has x and y coordinates
    // Now let's set values to x column and y line to INT_MAX
    edges[x][y] = INT_MAX; // Because we'll never return there

    checkedLines[y] = true;
    checkedColumns[x] = true;
    answer.push_back(make_pair(y,x));
}
