#include <algorithm>

#include "utils/intcode.hh"

int part_1(IntCode& ic, int limit) {
    int begin = 0;
    int res = 0;
    for (int y = 0; y < limit; y++) {
        int b, e;
        for (b = begin; b < limit; b++) {
            ic.start(b, y);
            if (ic.get_output()) break;
        }

        for (e = b; e < limit; e++) {
            ic.start(e, y);
            if (!ic.get_output()) break;
        }
        begin = b % limit;
        res += e - b;
    }

    return res;
}

int part_2(IntCode& ic, int square_size) {
    int begin = 0;
    int end = 0;
    vector<int> bv, ev;
    int y_min = 10;  // magic number
    int y = 0;
    while (true) {
        do {
            ic.start(++begin, y + y_min);
        } while (!ic.get_output());

        end = max(end, begin);
        do {
            ic.start(++end, y + y_min);
        } while (ic.get_output());

        bv.push_back(begin--);
        ev.push_back(end--);

        if ((y >= square_size) && (ev[y - square_size + 1] - bv[y] >= square_size)) {
            return 10000 * bv[y] + y - square_size + y_min + 1;
        }
        y += 1;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    IntCode ic(filename);

    cout << "Part 1 : " << part_1(ic, 50) << endl;
    cout << "Part 2 : " << part_2(ic, 100) << endl;

    return 0;
}