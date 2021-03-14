#include <algorithm>

#include "utils/intcode.hh"

int chain(vector<IntCode> &ics, vector<int> inputs, int initial) {
    int out = initial;
    int idx = 0;

    for (auto &ic : ics) {
        ic.init();
        ic.add_input(inputs[idx++]);
        ic.add_input(out);
        out = ic.run();
    }

    return out;
}

int chain_rec(vector<IntCode> &ics, vector<int> inputs, int initial) {
    int out = initial;
    int idx = 0;
    int prev_out = 0;

    for (auto &ic : ics) {
        ic.init();
        ic.add_input(inputs[idx++]);
    }

    idx = 0;
    while (out != -1) {
        prev_out = out;
        ics[idx].add_input(out);
        out = ics[idx].run();
        idx = (idx + 1) % 5;
    }

    return prev_out;
}

int part_1(vector<IntCode> &ics) {
    vector<int> inputs = {0, 1, 2, 3, 4};
    int max_out = 0;

    do {
        max_out = max(max_out, chain(ics, inputs, 0));
    } while (next_permutation(inputs.begin(), inputs.end()));

    return max_out;
}

int part_2(vector<IntCode> &ics) {
    vector<int> inputs = {5, 6, 7, 8, 9};
    int max_out = 0;

    do {
        max_out = max(max_out, chain_rec(ics, inputs, 0));
    } while (next_permutation(inputs.begin(), inputs.end()));

    return max_out;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];
    vector<IntCode> ics;
    auto program = IntCode(filename).program;

    for (int i = 0; i < 5; i++) {
        ics.push_back(IntCode(program));
    }

    cout << "Part 1 : " << part_1(ics) << endl;
    cout << "Part 2 : " << part_2(ics) << endl;

    return 0;
}