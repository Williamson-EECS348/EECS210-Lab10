/** REMEMBER TO INSERT HEADER COMMENT */
#include <iostream>

#include "matrix.h"

int main() {
    Matrix mat;
    mat.getMatrix();

    std::cout << "Got:\n";
    mat.printAdjacency();

    mat.dijkstra();
}