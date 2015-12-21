#include "baseTestLib.h"

void findTest(string taskname, string name, std :: ifstream& ifs) {
//Основной путь для поиска.
    ifs.open("../" + taskname + "/tests/" + name, std::ifstream::in);

    if(!ifs)
        ifs.open("../tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../../" + taskname + "/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../ninja_turtles/Tasks/" + taskname + "/tests/" + name, std::ifstream::in);
    if(!ifs)
        throw "test file " + name + " was not found";
}
