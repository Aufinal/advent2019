#include <iostream>
#include <tuple>

#include "utils/math.hh"
#include "utils/strings.hh"

bool test(int x, bool part2) {
    auto d = digits(x);
    int prev = -1;
    int run = 0;
    bool has_run = false;

    for (auto cur : d) {
        if (cur < prev) {
            return false;
        } else if (cur == prev) {
            run += 1;
        } else {
            has_run |= (run == 2 || (run > 2 && !part2));
            run = 1;
        }
        prev = cur;
    }
    has_run |= (run == 2 || (run > 2 && !part2));

    return has_run;
}

int main(int argc, char *argv[]) {
    int min = 123257;
    int max = 647015;

    int part1 = 0;
    int part2 = 0;
    for (int i = min; i <= max; i++) {
        part1 += (int)test(i, false);
        part2 += (int)test(i, true);
    }

    cout << "Part 1 : " << part1 << endl;
    cout << "Part 2 : " << part2 << endl;

    return 0;
}