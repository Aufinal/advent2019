#pragma once
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &str, const string &delim = ",") {
    vector<string> tokens;
    size_t prev = 0, pos = 0;

    do {
        pos = str.find(delim, prev);
        tokens.push_back(str.substr(prev, pos - prev));
        prev = pos + delim.length();
    } while (pos != string::npos);

    return tokens;
}

string replace(string str, const string &from, const string &to) {
    size_t start_pos = 0;

    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

vector<int> parseint(string filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        getline(file, line);
        file.close();
    }

    vector<int> res;
    for (auto c : line) res.push_back(c - '0');

    return res;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T> &c) {
    os << '[';
    if (!c.empty()) {
        copy(c.begin(), --c.end(), ostream_iterator<T>(os, ","));
        cout << c.back();
    }
    os << ']';
    return os;
}
