#include <fstream>
#include <iostream>

#include "utils/strings.hh"

vector<int> parse(string filename) {
    ifstream file(filename);
    string line;
    vector<int> res;

    if (file.is_open() && getline(file, line)) {
        for (auto c : line) {
            res.push_back(c - '0');
        }
    }

    return res;
}

int part_1(vector<int>& image, int x_len, int y_len) {
    int idx = 0, min = x_len * y_len, prod = 0;
    vector<int> count(3, 0);
    for (auto elt : image) {
        count[elt]++;
        idx += 1;

        if (!(idx % (x_len * y_len))) {
            if (count[0] < min) {
                min = count[0];
                prod = count[1] * count[2];
            }
            for (auto& elt : count) elt = 0;
        }
    }

    return prod;
}

void part_2(vector<int>& image, int x_len, int y_len) {
    for (int j = 0; j <= x_len; j++) cout << "\u2588\u2588";
    cout << endl;
    for (int i = 0; i < y_len; i++) {
        cout << "\u2588\u2588";
        for (int j = 0; j < x_len; j++) {
            int idx = x_len * i + j;
            while (image[idx] == 2) {
                idx += x_len * y_len;
            }

            cout << (image[idx] ? "  " : "\u2588\u2588");
        }
        cout << endl;
    }
    for (int j = 0; j <= x_len; j++) cout << "\u2588\u2588";
    cout << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    int x_len = 25;
    int y_len = 6;
    auto image = parse(filename);

    cout << "Part 1 : " << part_1(image, x_len, y_len) << endl;
    part_2(image, x_len, y_len);
}