#include "utils/intcode.hh"
#include "utils/math.hh"

using Panel = complex<int>;
using Hull = unordered_map<Panel, int>;

Hull paint(IntCode &ic, int start) {
    Panel pos(0, 0);
    complex<int> dir(0, 1);
    const complex<int> im(0, 1);
    Hull hull;
    ic.init();
    hull[pos] = start;

    while (ic.state != done) {
        ic.add_input(hull[pos]);
        ic.run();
        auto out = ic.get_outputs(2);
        hull[pos] = out[0];
        dir *= int(1 - 2 * out[1]) * im;
        pos += dir;
    }

    return hull;
}

int part_1(IntCode &ic) {
    auto board = paint(ic, 0);
    return board.size();
}

void part_2(IntCode &ic) {
    int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
    auto board = paint(ic, 1);

    for (auto [key, val] : board) {
        min_x = min(min_x, real(key));
        max_x = max(max_x, real(key));
        min_y = min(min_y, imag(key));
        max_y = max(max_y, imag(key));
    }

    for (int i = max_y; i >= min_y; i--) {
        for (int j = min_x; j <= max_x; j++) {
            cout << (board[Panel(j, i)] ? "  " : "\u2588\u2588");
        }
        cout << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    IntCode ic(filename);

    cout << "Part 1 : " << part_1(ic) << endl << endl;
    part_2(ic);

    return 0;
}