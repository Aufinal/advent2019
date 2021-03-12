#include <climits>
#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_map>

#include "utils/math.hh"
#include "utils/sets.hh"
#include "utils/strings.hh"

tuple<vector<string>, vector<string>> parse(string filename) {
    fstream file(filename);
    string line1;
    string line2;
    if (!(file.is_open() && getline(file, line1) && getline(file, line2))) throw 1;
    return make_tuple(split(line1), split(line2));
}

vector<complex<int>> traj(vector<string> cable) {
    const complex<int> im(0, 1);
    const complex<int> one(1, 0);
    vector<complex<int>> tr;
    complex<int> pos(0, 0);
    tr.push_back(pos);
    complex<int> dir;

    for (auto elt : cable) {
        int amount = stoi(elt.substr(1, elt.length()));
        switch (elt[0]) {
            case 'R':
                dir = one;
                break;
            case 'U':
                dir = im;
                break;
            case 'L':
                dir = -one;
                break;
            case 'D':
                dir = -im;
                break;
        }

        for (int k = 0; k < amount; k++) {
            pos += dir;
            tr.push_back(pos);
        }
    }

    return tr;
}

int part_1(vector<string> cable1, vector<string> cable2) {
    auto t1 = traj(cable1);
    auto t2 = traj(cable2);

    unordered_set<complex<int>> s1(t1.begin(), t1.end());
    unordered_set<complex<int>> s2(t2.begin(), t2.end());

    auto s = intersect(s1, s2);
    int min = INT_MAX;
    for (auto elt : s) {
        if (manhattan(elt) < min && manhattan(elt) != 0) min = manhattan(elt);
    }

    return min;
}

int part_2(vector<string> cable1, vector<string> cable2) {
    auto t1 = traj(cable1);
    auto t2 = traj(cable2);

    unordered_map<complex<int>, int> map;
    int i = 0;
    for (auto elt : t1) {
        map[elt] = i++;
    }

    int min = INT_MAX;
    int j = 0;
    for (auto elt : t2) {
        if (map.count(elt) && map[elt] + j < min && j != 0) min = map[elt] + j;
        j++;
    }

    return min;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];
    vector<string> cable1, cable2;
    tie(cable1, cable2) = parse(filename);

    cout << "Part 1 : " << part_1(cable1, cable2) << endl;
    cout << "Part 2 : " << part_2(cable1, cable2) << endl;

    return 0;
}