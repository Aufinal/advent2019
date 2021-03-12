#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> readlines_to_int(string filename) {
    vector<int> vec;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            vec.push_back(stoi(line));
        }
    }
    file.close();
    return vec;
}

int part_1(vector<int> &vec) {
    int sum = 0;
    for (auto &elt : vec) {
        sum += elt / 3 - 2;
    }

    return sum;
}

int part_2(vector<int> &vec) {
    int sum = 0;
    for (auto &&elt : vec) {
        while (elt > 5) {
            elt = elt / 3 - 2;
            sum += elt;
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];
    auto vec = readlines_to_int(filename);
    cout << "Part 1 : " << part_1(vec) << endl;
    cout << "Part 2 : " << part_2(vec) << endl;

    return 0;
}