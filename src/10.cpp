#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>

#include "utils/math.hh"
#include "utils/strings.hh"

vector<complex<int>> parse(string filename) {
    vector<complex<int>> res;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        int i = 0;
        while (getline(file, line)) {
            int j = 0;
            for (auto elt : line) {
                if (elt == '#') res.push_back(complex<int>(i, j));
                j++;
            }
            i++;
        }
    }

    return res;
}

int can_see(vector<complex<int>>& asteroids, complex<int> origin) {
    unordered_set<complex<int>> directions;

    for (auto ast : asteroids) {
        auto diff = ast - origin;
        if (diff == 0) continue;
        int d = gcd(real(diff), imag(diff));
        directions.insert(diff / d);
    }

    return directions.size();
}

struct argcomp {
    bool operator()(const complex<int>& lhs, const complex<int>& rhs) const {
        return argument(lhs) > argument(rhs);
    }
};

struct abscomp {
    bool operator()(const complex<int>& lhs, const complex<int>& rhs) const {
        return abs(lhs) > abs(rhs);
    }
};

vector<complex<int>> laser(vector<complex<int>>& asteroids, complex<int> origin) {
    map<complex<int>, priority_queue<complex<int>, vector<complex<int>>, abscomp>,
        argcomp>
        order;
    for (auto ast : asteroids) {
        auto diff = ast - origin;
        if (diff == 0) continue;
        int d = gcd(real(diff), imag(diff));
        order[diff / d].push(ast - origin);
    }

    vector<complex<int>> res;
    int n_remaining = asteroids.size() - 1;

    while (n_remaining) {
        for (auto& [key, val] : order) {
            if (!val.empty()) {
                res.push_back(val.top() + origin);
                val.pop();
                n_remaining--;
            }
        }
    }

    return res;
}

void part_12(vector<complex<int>>& asteroids) {
    int max = 0;
    complex<int> argmax;
    for (auto ast : asteroids) {
        auto cs = can_see(asteroids, ast);
        if (cs > max) {
            argmax = ast;
            max = cs;
        }
    }

    cout << "Part 1 : " << max << endl;
    cout << "Optimal ast : " << argmax << endl;

    auto res = laser(asteroids, argmax);
    cout << "Part 2 : " << res[199] << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    auto asteroids = parse(filename);
    part_12(asteroids);
}