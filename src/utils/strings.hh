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

vector<long> parseint(const vector<string> &vec) {
    vector<long> res;
    for (auto elt : vec) {
        res.push_back(stol(elt));
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