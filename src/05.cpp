#include "utils/intcode.hh"

int part_1(IntCode &ic) {
    int res;
    ic.start(1);
    while (ic.has_output()) {
        res = ic.get_output();
    }

    return res;
}

int part_2(IntCode &ic) {
    ic.start(5);
    return ic.get_output();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    auto ic = IntCode(filename);

    int res1 = part_1(ic);
    int res2 = part_2(ic);
    cout << "Part 1 : " << res1 << endl;
    cout << "Part 2 : " << res2 << endl;

    return 0;
}