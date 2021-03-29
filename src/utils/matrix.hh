#pragma once
#include <complex>
#include <fstream>
#include <iostream>
#include <vector>

#include "strings.hh"

using namespace std;

class Matrix {
    vector<long> data;

    int index(int x, int y) { return y * (size_x + 1) + x; }

   public:
    int size_x;
    int size_y;
    long& operator()(int x, int y) { return data[index(x, y)]; }
    long& operator[](complex<int> z) { return data[index(real(z), imag(z))]; }

    Matrix(vector<long> v) {
        size_x = find(v.begin(), v.end(), 10) - v.begin();
        size_y = v.size() / (size_x + 1);
        data = v;
    }

    Matrix(string filename) {
        fstream file(filename);
        std::stringstream buffer;

        if (file.is_open()) {
            buffer << file.rdbuf();
        }

        data = parsechar(buffer.str(), 0);
        size_x = find(data.begin(), data.end(), 10) - data.begin();
        size_y = data.size() / (size_x + 1);
    }

    void print() {
        for (auto elt : data) {
            cout << char(elt);
        }
    }
};