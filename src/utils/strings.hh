#pragma once
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

vector<int> parsechar(const string &str, char offset = '0') {
    vector<int> res;
    for (auto elt : str) {
        res.push_back(elt - offset);
    }

    return res;
}

template <class T>
string join(T &&vec, string delim = ",") {
    if (vec.empty()) return "";
    stringstream res;
    auto it = vec.begin();
    res << *it++;
    for (; it != vec.end(); it++) {
        res << delim << *it;
    }

    return res.str();
}