#include <iostream>
#include "transport.h"

//Here I'm going to locally test my transport task
//?

int main() {
	std :: cout << "Hello, World!" << std :: endl;
/*    vector <string> cities{"first", "second", "third", "zero", "fourth"};
    vector <way> ways;
    ways.push_back(way("first", "second", 40, Travel :: railway));
    ways.push_back(way("second", "third", 20, Travel :: road));
    ways.push_back(way("third", "fourth", 30, Travel :: railway));
    ways.push_back(way("zero", "fourth", 5, Travel :: road));
    ways.push_back(way("fourth", "second", 3, Travel :: railway));
    ways.push_back(way("third", "fourth", 6, Travel :: road));

    cout << "Transport answer: " << solveTransportTask(cities, ways) << endl;
*/

    vector <string> cities{"1", "2", "3", "4"};
    vector <way> ways;
    ways.push_back(way("1", "2", 2, Travel :: road));
    ways.push_back(way("2", "4", 1000, Travel :: road));
    ways.push_back(way("1", "3", 100, Travel :: road));
    ways.push_back(way("3", "4", 200, Travel :: road));

    cout << "Transport answer: " << solveTransportTask(cities, ways, "1", "4") << endl;
	return 0;
}
