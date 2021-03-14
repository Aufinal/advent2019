#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <tuple>

#include "strings.hh"

class IntCode {
    unordered_map<long, long> memory;
    queue<long> inputs;

    long cursor;
    long offset;

    tuple<short, short, short, short> _parse(int instr) {
        int t = instr % 100;
        instr /= 100;

        return make_tuple(t, instr % 10, (instr / 10) % 10, (instr / 100) % 10);
    }

   public:
    vector<long> program;
    IntCode(vector<long> prog) { program = prog; }
    IntCode(string filename) {
        ifstream file(filename);
        string line;
        if (file.is_open() && getline(file, line)) {
            program = parseint(split(line));
        }
    }

    void add_input() {}

    template <typename... Args>
    void add_input(long i, Args... args) {
        inputs.push(i);
        add_input(args...);
    }

    long read(short mode) {
        if (mode == 1) {
            return memory[cursor++];
        } else {
            long address = (mode / 2) * offset + memory[cursor++];
            return memory[address];
        }
    }

    void write(long value, short mode) {
        long address = (mode / 2) * offset + memory[cursor++];
        memory[address] = value;
    }

    long run() {
        while (true) {
            auto [opcode, m1, m2, m3] = _parse(memory[cursor++]);
            switch (opcode) {
                case 1: {
                    write(read(m1) + read(m2), m3);
                    break;
                }
                case 2: {
                    write(read(m1) * read(m2), m3);
                    break;
                }
                case 3: {
                    write(inputs.front(), m1);
                    inputs.pop();
                    break;
                }
                case 4:
                    return read(m1);
                case 5: {
                    if (read(m1) != 0) {
                        long new_cursor = read(m2);
                        cursor = new_cursor;
                    } else {
                        cursor++;
                    }
                    break;
                }
                case 6: {
                    if (read(m1) == 0) {
                        long new_cursor = read(m2);
                        cursor = new_cursor;
                    } else {
                        cursor++;
                    }
                    break;
                }
                case 7: {
                    long lhs = read(m1);
                    write(lhs < read(m2), m3);
                    break;
                }
                case 8: {
                    write(read(m1) == read(m2), m3);
                    break;
                }
                case 9: {
                    offset += read(m1);
                    break;
                }
                case 99:
                    return -1;
            }
        }

        return -2;
    }

    void init() {
        memory.clear();
        int idx = 0;
        for (auto elt : program) memory[idx++] = elt;
        cursor = 0;
        offset = 0;
        std::queue<long>().swap(inputs);
    }

    template <typename... Args>
    long start(Args... args) {
        init();
        add_input(args...);
        return run();
    }
};