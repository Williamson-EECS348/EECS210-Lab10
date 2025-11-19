#pragma once

#include <vector>
#include <ostream>
#include <ctype.h>

// these basically make long way of writing a row/matrix shorter and more readable
typedef std::vector<char> row_t;    // typedef for an individual matrix row
typedef std::vector<row_t> matrix_t;   // typedef for the matrix storage

class Matrix {
public:
    // default constructor, we dont do anything in our constructor so it is just the default
    Matrix() = default;

    // copy constructor
    Matrix(const matrix_t& m) : mat(m) {}

    // implementation of Dijkstra's algorithm
    void dijkstra();

    // gets user input and populates the matrix
    // this disobeys RAII but oh well
    void getMatrix();

    // helper functions:
    int getHeight() const;  // returns the height of the matrix
    int getWidth() const;   // returns the width of the matrix

    bool isSquare() const { return (getHeight() == getWidth()); }

    // allows for indexing of the object
    const row_t& operator[](size_t i) const;
    // allows for indexing of the object
    row_t& operator[](size_t i);

    void printAdjacency() const;

    // makes the class friendly to being printed
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m);

private:
    // used to parse user input
    row_t cleanup(std::string& input);

    // returns true if `c` is a character we dont want in our matrix (e.g. "," " " etc.)
    // make this static so it can be passed in as a function pointer to `remove_if()`
    static bool removeUnwanted(char c) { return (c == ',') || std::isspace(c); }

    static constexpr int toInt(char c) {
        if (std::isdigit(c))
            return static_cast<int>(c - '0');
        else
            return -1;
    }

public:
    // the underlying storage for the matrix
    matrix_t mat;
};