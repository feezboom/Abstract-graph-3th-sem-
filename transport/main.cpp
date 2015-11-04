#include <iostream>
#include "transport.h"

//Here I'm going to locally test my transport task
//?

int main() {
	std :: cout << "Hello, World!" << std :: endl;
    vector <string> cities{"first", "second", "third", "zero", "fourth"};
    vector <way> ways;
    ways.push_back(way("first", "second", 40, Travel :: railway));
    ways.push_back(way("second", "third", 20, Travel :: road));
    ways.push_back(way("third", "fourth", 30, Travel :: railway));
    ways.push_back(way("zero", "fourth", 5, Travel :: road));
    ways.push_back(way("fourth", "second", 3, Travel :: railway));
    ways.push_back(way("third", "fourth", 6, Travel :: road));

    solveTransportTask(cities, ways);

	return 0;
}
