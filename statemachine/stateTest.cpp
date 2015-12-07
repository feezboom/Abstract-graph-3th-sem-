#include <string>
#include <iostream>
#include "StateMachineGraph.h"

using namespace std;

int main(void) {
    cout << "Hello, StateMachine!" << endl;
    StateMachineGraph ourGraph;

    ourGraph.insert_vertex("abc");
    ourGraph.insert_vertex("bcdc");
    ourGraph.insert_vertex("cccb");
    ourGraph.insert_vertex("bcdd");
    ourGraph.insert_vertex("bbbc");

    ourGraph.solve("abcdcbcddbbbcccbbbcccbb");
//    ourGraph.solve("abcdc");

    return 0;
}