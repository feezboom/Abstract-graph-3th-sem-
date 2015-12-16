#ifndef _2SATTESTLIB_H_
#define _2SATTESTLIB_H_

#include "../2sat/2sat.h"
#include "../jsoncpp/include/json/json.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printStrongComponents(vector <vector <string>> components);
void findTest(string name, std :: ifstream& ifs);
bool test2Sat(string testName);

#endif // 2SATTESTLIB_H_
