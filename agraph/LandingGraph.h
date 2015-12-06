#ifndef _LANDINGGRAPH_H_
#define _LANDINGGRAPH_H_

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::to_string;

//*******************************************LANDING GRAPH****************************************************//
class LandingGraph {
public:
    LandingGraph() {}
    LandingGraph(int sizes[], vector<vector<vector<int>>> land, int airportPosition[], int planePosition[], int rotation[]) {
        if (sizes[0] < 0 || sizes[1] < 0 || sizes[2] < 0)
            throw "wrong space bounds";
        xSize = sizes[0];
        ySize = sizes[1];
        zSize = sizes[2];
        if (xSize != land.size() || ySize != land[0].size() || zSize != land[0][0].size())
            throw "wrong land heights vector size";

        for(int x = 0; x < xSize; ++x)
            for(int y = 0; y < ySize; ++y)
                for(int z = 0; z < zSize; ++z){
                    if (land[x][y][z] < 0 || land[x][y][z] > zSize) {
                        string message("wrong height in heights vector : [");
                        message += to_string(x);
                        message += "][";
                        message += to_string(y);
                        message += "][";
                        message += to_string(z);
                        message += "] == ";
                        message += to_string(land[x][y][z]);
                        throw message;
                    }
                        this->land[x][y][z] = land[x][y][z];
                }

        for(int i = 0; i < 3; ++i) {
            if (airportPosition[i] < 0 || planePosition[i] < 0)
                throw string("wrong plane or airport position");
            airportPos[i] = airportPosition[i];
            planePos[i] = planePosition[i];
        }
    }

    void insert_vertex(const string& name) {}
    void add_edge(const string& from, const string& to, double weight = 0) {}
    vector<vector<string>> Kosaraju() {}
    void transpose() {}

private:
    //Границы нужного пространства
    //Space x,y and z bounds
    int xSize, ySize, zSize;
    //Vector of heights of land
    //Как раз вектор высот земли
    vector<vector<vector<int>>> land;
    //Текущие позиции аэропорта и самолёта
    //Current positions of the plane and of the our airport
    int planePos[3], airportPos[3];
    int planeRotation, airportRotation;
};

#endif
