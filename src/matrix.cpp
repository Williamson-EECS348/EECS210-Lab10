#include "matrix.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <limits>
#include <algorithm>
#include <ctype.h>

/**
 * Translated from python:
 * Input:
 *  input can be delimited by either by spaces (' ') or commas (',') or both
 *  for example:
 *      1,0,1,0
 *      1 0 1 0
 *      1, 0, 1, 0
 *  and when input is done put in a blank line, should be just like python
 *
 * Creates a matrix in standard matrix notation:
 * M[x][y] is row x, (top to bottom, starting at 0)
 * and column y (left to right, starting at 0)
 * for example, a 3x3 matrix is
 * |(0,0) (0,1) (0,2)|
 * |(1,0) (1,1) (1,2)|
 * |(2,0) (2,1) (2,2)|
 */
void Matrix::getMatrix() {
    /**
     * Takes a matrix of numbers from the user. Each row can be
     * seperated by commas and/or spaces. A blank line ends the input
     */
    std::cout << "Enter your matrix:" << std::endl;
    std::string x{}; // the string to write to
    std::getline(std::cin, x); // need to getline because by default c++ splits on a space

    // `cleanup()` takes the string input and parses it into a row_t
    row_t items = cleanup(x);
    auto length = items.size(); // store how many columns the first row is

    // loop only until we take in as many rows as there are columns;
    // we already have 1 row so `i` starts at `1` and we want an equal number of rows and cols;
    //  this is techincally the same as if `i = 0` and `i < length` but its clearer this way
    for (int i = 1; i <= (int)length; i++) {
        if (i > 1) { // we only wany to ask if this isnt the first loop
            x = ""; // reset input string
            std::getline(std::cin, x); // need to getline because by default std::cin splits on a space
        }

        items = cleanup(x);
        // ensure that all of the next rows are the same length as first
        if (items.size() != length) {
            // if not then we tell the user the error and ask them to try again
            std::cerr << "ERROR: row lengths are mismatched! Try again:" << std::endl;
            // we want them to try again and so we remove one from the iterator;
            // so that we still get the correct number of rows
            i--;
        } else {
            mat.push_back(items);
        }
    }
}

/**
 * procedure Dijkstra(G: Weighted connected simple graph, with all weights positive)
 *  {G has vertices a = v0, v1, ..., vn = z and lengths w(vi, vj) where w(vi, vj) = ∞ if {vi, vj} is not an edge in G}
 *  for i := 1 to n
 *      L(vi) := ∞
 *  L(a) := 0
 *  S := ∅ {the labels are now initalized so that the label a is 0 and all other labels are ∞, and S is the empty set}
 *  while z ∉ S
 *      u := a vertex not in S with L(u) minimal
 *      S := S ∪ {u}
 *      for all vertices v not in S
 *          if L(u) + w(u, v) < L(v) then L(v) := L(u) + w(u, v)
 *          {this add a vertex to S with minimal label and updates the labels of vertices not in S}
 *  return L(z) {L(z) = length of a shortest path from a to z}
 */
void Matrix::dijkstra() {
    std::cout << "Please pick two vertices to go between (on one line seperated with a space): ";
    char first, second; // vertices to go between
    std::cin >> first >> second; // read in the vertices

    int start = int(first - 'a'); // convert from char to int index
    int end = int(second - 'a'); // convert from char to int index

    // run dijkstra's algorithm
    std::vector<int> L(getWidth(), std::numeric_limits<int>::max()); // initialize all labels to infinity
    L[start] = 0; // set starting vertex label to 0
    std::vector<bool> S(getWidth(), false); // initialize all vertices as not in S

    while (!S[end]) { // while end is not in S
        // find u
        int u = -1; // the vertex with minimal label not in S
        int minL = std::numeric_limits<int>::max(); // the minimal label found so far
        for (int i = 0; i < getWidth(); i++) { // for all vertices
            if (!S[i] && L[i] < minL) { // if vertex is not in S and has a smaller label than the smallest found so far
                minL = L[i]; // update smallest label
                u = i; // update vertex with smallest label
            }
        }

        S[u] = true; // add u to S

        for (int v = 0; v < getWidth(); v++) { // for all vertices v not in S
            int weight = toInt(mat[u][v]); // get weight of edge u-v
            if (!S[v] && weight != -1) { // if v is not in S and there is an edge u-v
                if (L[u] + weight < L[v]) { // if L(u) + w(u, v) < L(v)
                    L[v] = L[u] + weight; // update L(v)
                }
            }
        }
    }

    // list out the vertex path
    std::vector<int> path; // the path from start to end
    int current = end; // start from the end
    path.push_back(current); // add end to path
    while (current != start) { // while we have not reached the start
        // find the previous vertex in the path
        for (int i = 0; i < getWidth(); i++) { // for all vertices
            int weight = toInt(mat[i][current]); // get weight of edge i-current
            if (weight != -1 && L[current] - weight == L[i]) { // if there is an edge i-current and L(current) - w(i, current) == L(i)
                path.push_back(i); // add i to path
                current = i; // update current
                break; // break out of loop
            }
        }
    }
    std::reverse(path.begin(), path.end()); // reverse path to get from start to end

    for (const auto& c : path) { // print out the path
        std::cout << char('a' + c); // print vertex
        if (c != end) // if not at end
            std::cout << ','; // print comma
    }

    std::cout << '\t' << L[end] << std::endl; // print length of shortest path
}

// look at matrix.h to see these comments
int Matrix::getHeight() const { return static_cast<int>(mat.size()); }
int Matrix::getWidth() const { return static_cast<int>(mat[0].size()); }
const row_t& Matrix::operator[](size_t i) const { return mat[i]; }
row_t& Matrix::operator[](size_t i) { return mat[i]; }

// cleanup the input string and return it as a row_t (i.e. a std::vector of unsigned bytes)
row_t Matrix::cleanup(std::string& input) {
    // Source: https://stackoverflow.com/a/83538/16902023
    // this will erase all unwanted characters from `input` using the `removeUnwanted()`
    // it will remove "," and spaces
    input.erase(remove_if(input.begin(), input.end(), removeUnwanted), input.end());

    // make the new matrix row
    row_t items; // initalize the row to be the size of the string so we dont need to move it while creating it
    // for every character in the input string
    for (char c : input) {
        // add the input to the back
        items.push_back(c);
    }

    // return the row, I don't love returning the row like this since copying a
    //  vector is not the best but its good enough; return value optimization will hopefully handle it
    return items;
}

void Matrix::printAdjacency() const {
    // print header
    int w = getWidth();
    int h = getHeight();
    std::cout << "  ";
    for (int i = 0; i < w; i++)
        std::cout << char('a' + i) << ' ';
    std::cout << '\n';

    for (int j = 0; j < h; j++) {
        std::cout << char('a' + j) << ' ';
        for (char item : mat[j]) {
            std::cout << item << ' ';
        }
        std::cout << '\n';
    }
}

// Source: https://en.cppreference.com/w/cpp/language/operators.html#Stream_extraction_and_insertion
// allows for the class object to 'play nice' with `std::cout` printing
std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    for (const row_t& row : m.mat) {
        for (char item : row) {
            out << item << ' ';
        }
        out << '\n';
    }

    return out;
}