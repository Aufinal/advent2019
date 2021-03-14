#include "utils/intcode.hh"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    auto ic = IntCode(filename);

    // int res2 = part_2(ic);
    cout << "Part 1 : " << ic.start(1) << endl;
    cout << "Part 2 : " << ic.start(2) << endl;

    return 0;
}