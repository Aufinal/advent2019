#include "utils/intcode.hh"

int part_1(IntCode &ic) {
    ic.init();
    ic.add_input(1);
    int res;
    do {
        res = ic.run();
    } while (res == 0);

    return res;
}

int part_2(IntCode &ic) {
    ic.init();
    ic.add_input(5);
    return ic.run();
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