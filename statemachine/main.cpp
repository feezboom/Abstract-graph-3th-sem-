#include <string>
#include <iostream>
#include "StateMachineGraph.h"

using namespace std;

int main(void) {
    cout << "Hello, StateMachine!" << endl;
    StateMachineGraph ourGraph;

    ourGraph.insert_vertex("Hello");

    return 0;
}