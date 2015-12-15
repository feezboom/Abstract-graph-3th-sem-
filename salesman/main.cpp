#include <iostream>
#include <limits.h>
#include "SalesmanGraph.h"
// Хочу сделать json cpp системной библиотекой?


using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    SalesmanGraph a = SalesmanGraph();

    a.insert_vertex("1");
    a.insert_vertex("2");
    a.insert_vertex("3");
    a.insert_vertex("4");

    a.add_edge("1", "1", INT_MAX);
    a.add_edge("1", "2", 5);
    a.add_edge("1", "3", 11);
    a.add_edge("1", "4", 9);

    a.add_edge("2", "1", 10);
    a.add_edge("2", "2", INT_MAX);
    a.add_edge("2", "3", 8);
    a.add_edge("2", "4", 7);

    a.add_edge("3", "1", 7);
    a.add_edge("3", "2", 14);
    a.add_edge("3", "3", INT_MAX);
    a.add_edge("3", "4", 8);

    a.add_edge("4", "1", 12);
    a.add_edge("4", "2", 6);
    a.add_edge("4", "3", 15);
    a.add_edge("4", "4", INT_MAX);

    int answer = a.solveTask();
    cout << answer;

    return 0;
}