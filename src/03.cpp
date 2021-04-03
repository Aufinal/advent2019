#include <climits>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "utils/math.hh"
#include "utils/strings.hh"

pair<vector<string>, vector<string>> parse(string filename) {
    fstream file(filename);
    string line1, line2;

    if (file.is_open()) {
        getline(file, line1);
        getline(file, line2);
        file.close();
    }

    return make_pair(split(line1), split(line2));
}

vector<complex<int>> traj(vector<string> cable) {
    complex<int> one(1, 0), im(0, 1);
    const unordered_map<char, complex<int>> directions = {
        {'R', one}, {'U', im}, {'L', -one}, {'D', -im}};

    vector<complex<int>> tr;
    complex<int> pos(0, 0);

    for (auto elt : cable) {
        int amount = stoi(elt.substr(1));
        auto dir = directions.at(elt[0]);

        while (amount--) {
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

    unordered_set<complex<int>> intersection;
    for (auto elt : t2) {
        if (s1.contains(elt)) intersection.insert(elt);
    }

    int min = INT_MAX;
    for (auto elt : intersection) {
        if (manhattan(elt) < min && manhattan(elt) != 0) min = manhattan(elt);
    }

    return min;
}

int part_2(vector<string> cable1, vector<string> cable2) {
    auto t1 = traj(cable1);
    auto t2 = traj(cable2);

    unordered_map<complex<int>, int> map;
    int i = 1;
    for (auto elt : t1) {
        map[elt] = i++;
    }

    int min = INT_MAX;
    int j = 1;
    for (auto elt : t2) {
        if (map.contains(elt) && map[elt] + j < min) min = map[elt] + j;
        j++;
    }

    return min;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    auto [cable1, cable2] = parse(filename);

    cout << "Part 1 : " << part_1(cable1, cable2) << endl;
    cout << "Part 2 : " << part_2(cable1, cable2) << endl;

    return 0;
}