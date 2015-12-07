#include <iostream>
#include <fstream>
#include <cmath>
#include <assert.h>

using namespace std;

int pow(int x, int i) {
    assert(i >= 0);
    int ans = 1;
    for (int k = 0; k < i; ++k)
        ans *= x;
    return ans;
}

#define min(x,y) (x < y ? x : y)
#define min3(x, y, z) (min(x,y) < z ? min(x,y) : z)
#define min4(x, y, z, w) (min3(x, y, z) < w ? min3(x, y, z) : w)

int main() {
    cout << "Hello, World!" << endl;
    int dimx = 3;
    int dimy = 3;

    int a[dimx][dimy];
    int table[dimx][dimy][dimx][dimy];

    fstream file;
    file.open("/home/avk/Documents/ninja_turtles/waterway/input.txt");

    for (int i = 0; i < dimx; ++i)
        for (int j = 0; j < dimy; ++j) {
            file >> a[i][j];
            // Первый слой sparse table
            table[0][0][i][j] = a[i][j];
        }

    // Заполняем sparse table дальше
    for (int l = 1; l <= log(dimx); ++l) {
        for (int m = 1; m <= log(dimy); ++m) {
            for (int i = 0; i < dimx - pow(2, l); ++i) {
                for (int j = 0; j < dimy - pow(2, m); ++j) {
                    table[l][m][i][j] = min4(
                            table[l-1][m][i][j],
                            table[l-1][m][i + pow(2, l-1)][j],
                            table[l][m-1][i][j],
                            table[l][m-1][i][j + pow(2, m-1)]);
                }
            }
        }
    }

    // Ищем ответ для запроса, используя sparse table


    return 0;
}