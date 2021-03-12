#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string &s, char c = ',') {
    vector<string> v;
    int i = 0;
    int j = s.find(c);

    while (j != string::npos) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == string::npos) v.push_back(s.substr(i, s.length()));
    }

    return v;
}

vector<int> parseint(const vector<string> &vec) {
    vector<int> res;
    for (auto elt : vec) {
        res.push_back(stoi(elt));
    }

    return res;
}

template <class T>
string join(T &&vec, string delim = ",") {
    stringstream res;
    auto it = vec.begin();
    res << *it++;
    for (; it != vec.end(); it++) {
        res << delim << *it;
    }

    return res.str();
}