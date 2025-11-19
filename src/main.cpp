/** REMEMBER TO INSERT HEADER COMMENT */
#include <iostream>

#include "matrix.h"

int main() {
    Matrix mat;
    mat.mat = {
        {'*','6','3','*'},
        {'6','*','4','1'},
        {'3','4','*','1'},
        {'*','1','1','*'}
    };

    std::cout << "Got:\n";
    mat.printAdjacency();

    mat.dijkstra();
}