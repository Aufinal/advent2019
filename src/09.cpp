#include "utils/intcode.hh"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw invalid_argument("Must supply filename !");
    }
    string filename = argv[1];

    auto ic = IntCode(filename);

    ic.start(1);
    auto res1 = ic.get_output();
    ic.start(2);
    auto res2 = ic.get_output();

    cout << "Part 1 : " << res1 << endl;
    cout << "Part 2 : " << res2 << endl;

    return 0;
}